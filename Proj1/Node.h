#ifndef NODE_H
#define NODE_H

class Node {
    private:
        State curr;
        Node* parent;
        int depth;
        string key;

    public:
        Node() : parent(NULL), depth(0) { curr = State(); key = hash(); }
        Node(State c) : curr(c), parent(NULL), depth(0) { key = hash(); }
        Node(State c, Node* p, int d) : curr(c), parent(p), depth(d) { key = hash(); }
        ~Node() { delete parent; }

        State get_curr() { return curr; }
        int get_depth() { return depth; }
        bool goal_test(State*); // checks whether this state matches another (like the goal)
        vector<Node*> successors(); // gets the successors of the state, and wraps them in Nodes
        string hash(); // return hash key of state
        int print_path(); // print sequence of states from root down to this
};

#endif
