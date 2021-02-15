#include <iostream>

#include "Node.h"

using namespace std;

bool Node::goal_test(State* s) {
    return curr.match(s);
}

vector<Node*> Node::successors() {
    vector<State*> moves = curr.successors();
    vector<Node*> moves_nodes;
    
    vector<State*>::iterator iter;
    for (iter=moves.begin(); iter!=moves.end(); iter++) {
        Node* successor = new Node(**iter, this);
        moves_nodes.push_back(successor);
    }

    return moves_nodes;
}

string Node::hash() {
    return curr.get_key();
}

int Node::print_path() {
    int i=0;
    if (parent != NULL) i = parent->print_path();

    cout << "[MOVE " << i << "]\n";
    get_curr().print();
    cout << ">>>>>>>>>>\n";

    return i+1;
}
