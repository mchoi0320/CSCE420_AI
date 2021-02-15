#include <string>
#include <vector>

using namespace std;

class State {
    private:
        vector<vector<char> > curr;
        int num_stacks;
        string key;

    public:
        State() : num_stacks(0), key("") {}
        // State(vector<vector<char> > s, int n) : curr(s), num_stacks(n) { hash(); }
        State(vector<vector<char> > s, int n) : curr(s), num_stacks(n) { key = hash(); }

        string get_key() { return key; }
        void print(); // for printing out a state (in the horizontal format)
        bool match(State*); // tell whether 2 states are equal, for goal-testing
        string hash(); // generate a “key” unique to each state for tracking Visited
        vector<State*> successors(); // generate all children of this state given all legal moves
};