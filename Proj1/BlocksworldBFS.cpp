#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <utility>

// #include "State.h"
#include "Node.h"

using namespace std;

Node* BFS(Node* init, State goal) {
    
    if (init->goal_test(&goal)) return init;

    queue<Node*> frontier;
    frontier.push(init);

    unordered_map<string, bool> explored;

    while (!frontier.empty()) {
        Node* node = frontier.front();
        frontier.pop();
        
        vector<Node*> nodes = node->successors();
        vector<Node*>::iterator iter;
        for (iter=nodes.begin(); iter!=nodes.end(); iter++) {
            State s = (*iter)->get_curr();
            Node* n = new Node(s, node);

            if (s.match(&goal)) return n;

            if (explored.find(s.get_key()) == explored.end()) {
                explored.insert(make_pair<string, bool>(s.get_key(), true));
                frontier.push(n);
            }
        }
    }

    Node* fail = new Node();
    return fail;
}

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
    // vector<vector<char> > stacks_init, stacks_goal;

    // for (int k=0; k<2; k++) {
    //     getline(f, line); // separator line

    //     for (int i=0; i<num_stacks; i++) {
    //         vector<char> stack;

    //         getline(f, line);
    //         for (int j=0; j<line.length(); j++) stack.push_back(line[j]);

    //         if (k == 0) stacks_init.push_back(stack);
    //         else stacks_goal.push_back(stack);
    //     }
    // }

    f.close();

    State init(stacks_init, num_stacks);
    State goal(stacks_goal, num_stacks);
    // init.print();
    // goal.print();
    // cout << init.match(&goal) << endl;
    // vector<State*> moves = init.successors();
    // vector<State*>::iterator iter;
    // for (iter=moves.begin(); iter!=moves.end(); iter++) {
    //     (*iter)->print();
    //     cout << endl;
    // }
    // for (int i=0; i<moves.size(); i++) {
    //     moves[i].print();
    //     cout << endl;
    // }
    // Node n(&init, moves[0]);
    // cout << n.goal_test(&goal) << endl;
    Node start(init);
    // vector<Node*> moves = start.successors();
    // vector<Node*>::iterator iter;
    // for (iter=moves.begin(); iter!=moves.end(); iter++) {
    //     (*iter)->get_curr().print();
    //     cout << endl;
    // }
    // moves[0]->print_path(moves[0], 0);
    // vector<vector<char> > t;
    // cout << t.size() << endl;
    Node* end = BFS(&start, goal);
    end->print_path(end, 0);

    cout << "\n---Program ends here---\n";
}