#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <tuple>

// #include "State.h"
#include "Node.h"

using namespace std;

#define MAX_ITERS 1e6 // sets the BFS iteration limit to 1,000,000

// smplementation of Breadth-First Search
tuple<Node*, unsigned int, int, int> BFS(Node* init, State goal) {

    // summary statistics
    unsigned int max_frontier_size=0;
    int num_iters=0, depth=0;

    if (init->goal_test(&goal)) return tuple<Node*, unsigned int, int, int>(init, max_frontier_size, num_iters, depth);

    queue<pair<Node*, int> > frontier;
    frontier.push(pair<Node*, int>(init, depth));
    max_frontier_size = frontier.size();

    unordered_map<string, Node*> explored; // for keeping track of visited nodes
    
    while (!frontier.empty() && num_iters < MAX_ITERS) {

        pair<Node*, int> node = frontier.front();
        frontier.pop();
        
        vector<Node*> nodes = node.first->successors();
        vector<Node*>::iterator iter;
        for (iter=nodes.begin(); iter!=nodes.end(); iter++) {
            num_iters++;

            // print out summary statistics every 1000 iterations
            if (num_iters % 1000 == 0) {
                cout << "Current---Iteration: " << num_iters << " | " << "Depth: " << depth << " | " << "Maximum Frontier Size: " << max_frontier_size << endl;
            }

            State s = (*iter)->get_curr();
            Node* n = new Node(s, node.first);

            if (s.match(&goal)) {
                // nodes.clear();                           // an attempt to
                // queue<pair<Node*, int> > empty;          // fix memory leaks...
                // swap(frontier, empty);                   // didn't work
                cout << "----------\n";
                return tuple<Node*, unsigned int, int, int>(n, max_frontier_size, num_iters, depth);
            }

            if (explored.find(s.get_key()) == explored.end()) {
                explored.insert(pair<string, Node*>(s.get_key(), n));
                frontier.push(pair<Node*, int>(n, node.second+1));

                if (frontier.size() > max_frontier_size) max_frontier_size = frontier.size();
            }
        }

        depth = node.second+1;
    }

    cout << "----------\n";

    Node* fail = new Node(); // failure returns an "empty" node
    return tuple<Node*, unsigned int, int, int>(fail, max_frontier_size, num_iters, depth);
}

// parsing the input file
vector<vector<char> > get_state(ifstream& f, int n) {
    
    vector<vector<char> > stacks;

    string line;
    getline(f, line); // separator line
    for (int i=0; i<n; i++) {
        vector<char> stack;

        getline(f, line);
        for (int j=0; j<line.length(); j++) stack.push_back(line[j]);

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
    tuple<Node*,unsigned int, int, int> solution = BFS(&problem, goal);

    // print summary statistics and path (if successful)
    if (get<0>(solution)->get_curr().get_key() != "") {
        cout << "Success!\n";
        cout << "Iterations: " << get<2>(solution) << " | " << "Depth: " << get<3>(solution) << " | " << "Maximum Frontier Size: " << get<1>(solution) << endl;
        cout << ">>>>>>>>>>\n";
        get<0>(solution)->print_path();
    }
    
    else {
        cout << "Failure! Path to goal could not be found.\n";
        cout << "Iterations: " << get<2>(solution) << " | " << "Depth: " << get<3>(solution) << " | " << "Maximum Frontier Size: " << get<1>(solution) << endl;
    }
}
