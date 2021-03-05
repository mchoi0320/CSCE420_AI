#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <iomanip>

#include "State.h"
#include "Node.h"

using namespace std;

#define NUM_TEST_FILES 45
#define MAX_ITERS 100000 // sets the BFS iteration limit to 100,000

// implementation of A*
Node* Astar(Node* init, State goal, ofstream& f, bool all) {

    // summary statistics
    unsigned int max_frontier_size=0;
    int depth=0, num_iters=0;

    if (init->goal_test(&goal)) {
        if (all) {
            cout << "-----------\nSuccess!\n";
            cout << "The problem state matches the goal state.\n";
            f << " Success! The problem state matches the goal state.";
        }
        else {
            cout << "----------\nSuccess!\n";
            cout << "The problem state matches the goal state.\n";
            f << "\nSuccess!\n";
            f << "The problem state matches the goal state.\n";
        }

        return init;
    }

    priority_queue<Node*, vector<Node*>, MinPQ> frontier;
    frontier.push(init);
    max_frontier_size = frontier.size();

    unordered_map<string, Node*> explored; // for keeping track of visited nodes
    explored[init->get_curr().get_key()] = init;
    
    while (!frontier.empty() && num_iters < MAX_ITERS) {

        Node* node = frontier.top();
        frontier.pop();
        
        vector<Node*> nodes = node->successors();
        for (vector<Node*>::iterator iter=nodes.begin(); iter!=nodes.end(); ++iter) {
            depth = (*iter)->get_depth();
            ++num_iters;

            if (!all) {
                // print out summary statistics every 1000 iterations
                if (num_iters % 1000 == 0) {
                    cout << "Current---Iteration: " << num_iters << " | Depth: " << depth << " | Maximum Frontier Size: " << max_frontier_size << endl;
                }
            }

            if ((*iter)->goal_test(&goal)) {
                if (all) {
                    cout << "-----------\nSuccess!\n";
                    cout << "Iterations: " << num_iters << " | Depth: " << depth << " | Maximum Frontier Size: " << max_frontier_size << endl;
                    f << " Success! Iterations: " << setw(6) << right << num_iters
                      << " | Depth: " << setw(3) << right << depth
                      << " | Maximum Frontier Size: " << setw(6) << right << max_frontier_size;
                }
                else {
                    cout << "----------\nSuccess!\n";
                    cout << "Iterations: " << num_iters << " | Depth: " << depth << " | Maximum Frontier Size: " << max_frontier_size << endl;
                    f << "\nSuccess!\n";
                    f << "Iterations: " << num_iters << " | Depth: " << depth << " | Maximum Frontier Size: " << max_frontier_size << endl;
                }

                return *iter;
            }

            if (explored.find((*iter)->get_curr().get_key()) == explored.end() || (*iter)->get_depth() < explored[(*iter)->get_curr().get_key()]->get_depth()) {
                explored[(*iter)->get_curr().get_key()] = *iter;
                frontier.push(*iter);

                if (frontier.size() > max_frontier_size) max_frontier_size = frontier.size();
            }
        }
    }

    if (all) {
        cout << "-----------\nFailure!\n";
        cout << "Path to goal could not be found.\n";
        f << " Failure!";
    }
    else {
        cout << "----------\nFailure!\n";
        cout << "Path to goal could not be found.\n";
        cout << "Iterations: " << num_iters << " | Depth: " << depth << " | Maximum Frontier Size: " << max_frontier_size << endl;
        f << "\nFailure!\n";
        f << "Path to goal could not be found.\n";
        f << "Iterations: " << num_iters << " | Depth: " << depth << " | Maximum Frontier Size: " << max_frontier_size << endl;
    }

    Node* fail = new Node(); // failure returns an "empty" node
    return fail;
}

// parsing the input file
vector<vector<char> > get_state(ifstream& f, int n) {
    
    vector<vector<char> > stacks;

    string line;
    getline(f, line); // separator line
    for (int i=0; i<n; ++i) {
        vector<char> stack;

        getline(f, line);
        for (int j=0; j<line.length(); ++j) stack.push_back(line[j]);

        stacks.push_back(stack);
    }

    return stacks;
}

int main(int argc, char** argv) {

    if (argc < 2) {
        ofstream stats("STATISTICS.txt", ofstream::trunc);
        stats << "==================== STATISTICS ====================\n\n";
        stats << setw(15) << left << "FILE";
        stats << setw(4) << right << "S";
        stats << setw(4) << right << "B";
        stats << setw(6) << right << "N";
        stats << setw(8) << right << "OUTCOME";
        stats << endl;

        int tests_passed=0;
        for (int i=1; i<NUM_TEST_FILES+1; ++i) {
            string filename;
            ifstream f;
            if (i < 10) {
                filename = "bwchp0" + to_string(i) + ".bwp";
                stats << setw(15) << left << filename;
                f.open("BWCHP/" + filename);
                cout << filename << endl;
            }
            else {
                filename = "bwchp" + to_string(i) + ".bwp";
                stats << setw(15) << left << filename;
                f.open("BWCHP/" + filename);
                cout << filename << endl;
            }

            string inputs, line;

            int num_stacks, num_blocks, num_moves;
            getline(f, inputs);
            istringstream ss(inputs);
            ss >> num_stacks;
            ss >> num_blocks;
            ss >> num_moves;
            
            stats << setw(4) << right << num_stacks;
            stats << setw(4) << right << num_blocks;
            stats << setw(6) << right << num_moves;

            vector<vector<char> > stacks_init = get_state(f, num_stacks);
            vector<vector<char> > stacks_goal = get_state(f, num_stacks);

            f.close();

            State init(stacks_init, num_stacks);
            State goal(stacks_goal, num_stacks);

            Node problem(init, goal);
            Node* solution = Astar(&problem, goal, stats, true);

            cout << endl;
            stats << endl;

            if (solution->get_curr().get_key() != "") ++tests_passed;
        }

        cout << "\nNumber of tests passed: " << tests_passed << " out of " << NUM_TEST_FILES << endl;
        stats << "\nNumber of tests passed: " << tests_passed << " out of " << NUM_TEST_FILES;

        stats.close();
    }
    
    else {
        ifstream f;
        f.open(argv[1]);
        
        string inputs, line;

        int num_stacks, num_blocks, num_moves;
        getline(f, inputs);
        istringstream ss(inputs);
        ss >> num_stacks;
        ss >> num_blocks;
        ss >> num_moves;
        
        vector<vector<char> > stacks_init = get_state(f, num_stacks);
        vector<vector<char> > stacks_goal = get_state(f, num_stacks);

        f.close();

        int start = string(argv[1]).find("/");
        int end = string(argv[1]).find(".");
        string filename = string(argv[1]).substr(start+1, end-start-1);
        ofstream results("OUTPUT/" + filename + ".out", ofstream::trunc);

        results << "==================== " << filename << ".bwp ====================\n";

        State init(stacks_init, num_stacks);
        State goal(stacks_goal, num_stacks);

        Node problem(init, goal);
        Node* solution = Astar(&problem, goal, results, false);

        // print path only if: (1) the solution does not match the problem and (2) the solution is not an "empty" node a.k.a. a failure
        if (solution != &problem && solution->get_curr().get_key() != "") {
            cout << ">>>>>>>>>>\n";
            solution->print_path();

            results << ">>>>>>>>>>\n";
            results << solution->print_to_file().second;
        }

        results.close();
    }
}
