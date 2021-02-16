#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <utility>

#include "State.h"
#include "Node.h"

using namespace std;

#define MAX_ITERS 5e6 // sets the BFS iteration limit to 5,000,000

// implementation of Breadth-First Search
Node* BFS(Node* init, State goal) {

    // summary statistics
    unsigned int max_frontier_size=0;
    int num_iters=0, depth=0;

    if (init->goal_test(&goal)) {
        cout << "----------\nSuccess!\n";
        cout << "The problem state matches the goal state.\n";
        return init;
    }

    queue<pair<Node*, int> > frontier;
    frontier.push(pair<Node*, int>(init, depth));
    max_frontier_size = frontier.size();

    unordered_map<string, Node*> explored; // for keeping track of visited nodes
    
    while (!frontier.empty() && num_iters < MAX_ITERS) {

        pair<Node*, int> node = frontier.front();
        frontier.pop();
        
        vector<Node*> nodes = node.first->successors();
        depth = node.second+1;
        for (vector<Node*>::iterator iter=nodes.begin(); iter!=nodes.end(); ++iter) {
            ++num_iters;

            // print out summary statistics every 1000 iterations
            if (num_iters % 1000 == 0) {
                cout << "Current---Iteration: " << num_iters << " | " << "Depth: " << depth << " | " << "Maximum Frontier Size: " << max_frontier_size << endl;
            }

            State s = (*iter)->get_curr();
            Node* n = new Node(s, node.first);

            if (s.match(&goal)) {
                // queue<pair<Node*, int> > empty;          // an attempt to fix memory leaks
                // swap(frontier, empty);                   // based on some Google searches...
                // nodes.clear();                           // didn't work (understandable)

                // for (Node* p : nodes) delete p;          // another attempt... the for loop results in an
                // nodes.clear();                           // error: double free or corruption

                // while (!frontier.empty()) {              // more attempts, but
                //     delete frontier.front().first;       // this is another double free or corruption error and
                //     frontier.pop();                      // this didn't change anything...
                // }                                        // I'm completely lost x_x

                cout << "----------\nSuccess!\n";
                cout << "Iterations: " << num_iters << " | " << "Depth: " << depth << " | " << "Maximum Frontier Size: " << max_frontier_size << endl;

                return n;
            }

            if (explored.find(s.get_key()) == explored.end()) {
                explored.insert(pair<string, Node*>(s.get_key(), n));
                frontier.push(pair<Node*, int>(n, depth));

                if (frontier.size() > max_frontier_size) max_frontier_size = frontier.size();
            }
        }
    }

    cout << "----------\nFailure!\n";
    cout << "Path to goal could not be found.\n";
    cout << "Iterations: " << num_iters << " | " << "Depth: " << depth << " | " << "Maximum Frontier Size: " << max_frontier_size << endl;

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

    // check that file name is given
    if (argc < 2) {
        cout << "Please provide a file name in the command line." << endl;
        exit(1);
    }
    
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

    State init(stacks_init, num_stacks);
    State goal(stacks_goal, num_stacks);

    Node problem(init);
    Node* solution = BFS(&problem, goal);

    // print path only if: (1) the solution does not match the problem and (2) the solution is not an "empty" node a.k.a. a failure
    if (solution != &problem && solution->get_curr().get_key() != "") {
        cout << ">>>>>>>>>>\n";
        solution->print_path();    
    }

    // delete solution;         // also double free or corruption which makes sense... so how do I fix the leaks?!
}
