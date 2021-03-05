#include <iostream>
#include <sstream>

#include "State.h"
#include "Node.h"

using namespace std;

bool Node::goal_test(State* s) {
    return curr.match(s);
}

vector<Node*> Node::successors() {
    vector<State*> moves = curr.successors();
    vector<Node*> moves_nodes;
    
    for (vector<State*>::iterator iter=moves.begin(); iter!=moves.end(); ++iter) {
        Node* successor = new Node(**iter, goal, this, depth+1);
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

pair<int, string> Node::print_to_file() {
    int i=0;
    string str="";
    pair<int, string> temp(i, str);
    if (parent != NULL) temp = parent->print_to_file();

    stringstream ss;
    ss << temp.first;

    temp.second += "[MOVE " + ss.str() + "]\n";
    temp.second += get_curr().to_file();
    temp.second += ">>>>>>>>>>\n";

    ++temp.first;

    return temp;
}