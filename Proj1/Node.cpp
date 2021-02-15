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

int Node::print_path(Node* n, int d) {
    if (n->parent != NULL) d = print_path(n->parent, d);

    cout << "[MOVE " << d << "]\n";
    n->get_curr().print();
    cout << ">>>>>>>>>>\n";
    return d+1;
}