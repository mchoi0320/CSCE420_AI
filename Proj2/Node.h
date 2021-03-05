#ifndef NODE_H
#define NODE_H

class Node {
    private:
        State curr;
        State goal;
        Node* parent;
        int depth;
        string key;
        float f;

    public:
        Node() : parent(NULL), depth(0), f(0) { curr = State(); goal = State(); key = hash(); }
        Node(State c, State g) : curr(c), goal(g), parent(NULL), depth(0) { key = hash(); f = depth + curr.heuristic(g); }
        Node(State c, State g, Node* p, int d) : curr(c), goal(g), parent(p), depth(d) { key = hash(); f = depth + curr.heuristic(g); }
        ~Node() { delete parent; }

        State get_curr() { return curr; }
        int get_depth() { return depth; }
        float get_heuristic() { return f; }
        bool goal_test(State*); // checks whether this state matches another (like the goal)
        vector<Node*> successors(); // gets the successors of the state, and wraps them in Nodes
        string hash(); // return hash key of state
        int print_path(); // print sequence of states from root down to this
        pair<int, string> print_to_file();
};

class MinPQ {
    public:
        bool operator()(Node* n1, Node* n2) { return n1->get_heuristic() > n2->get_heuristic(); }
};

#endif
