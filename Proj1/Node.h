#include "State.h"

class Node {
    private:
        State curr;
        Node* parent;
        string key;

    public:
        Node() : parent(NULL), key("") { curr = State(); }
        Node(State c) : curr(c), parent(NULL) { key = hash(); }
        Node(State c, Node* p) : curr(c), parent(p) { key = hash(); }
        ~Node() { delete parent; }

        State get_curr() { return curr; }
        bool goal_test(State*); // checks whether this state matches another (like the goal)
        vector<Node*> successors(); // gets the successors of the state, and wraps them in Nodes
        string hash(); // return hash key of state
        int print_path(); // print sequence of states from root down to this
};
