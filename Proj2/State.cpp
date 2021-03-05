#include <iostream>

#include "State.h"

using namespace std;

void State::print() {
    for (int i=0; i<key.length(); ++i) {
        if (key[i] == ';') cout << endl;
        else cout << key[i];
    }
    cout << endl;
}

string State::to_file() {
    string str="";
    for (int i=0; i<key.length(); ++i) {
        if (key[i] == ';') str += "\n";
        else str += key[i];
    }
    str += "\n";

    return str;
}

bool State::match(State* s) {
    return (key == s->get_key());
}

string State::hash() {
    // serializing the object
    string str = "";
    for (int i=0; i<num_stacks; ++i) {
        for (int j=0; j<curr[i].size(); ++j) str += curr[i][j];
        if (i != num_stacks-1) str += ';';
    }

    return str;
}

vector<State*> State::successors() {
    vector<State*> moves;

    for (int i=0; i<num_stacks; ++i) {
        if (!curr[i].empty()) { // curr[i] is the current stack that a block is being moved from
            for (int j=0; j<num_stacks; ++j) {
                if (i != j) { // no need to "move" a block to the stack it was already in
                    vector<vector<char> > temp = curr;
                    temp[j].push_back(temp[i][temp[i].size()-1]);
                    temp[i].erase(temp[i].end()-1);

                    State* move = new State(temp, num_stacks);
                    moves.push_back(move);
                }
            }
        }
    }

    return moves;
}

vector<string> State::get_stacks(State s) {
    vector<string> stacks;

    string str = s.get_key(), stack;
    int start=0, pos;

    while (str.find(";", start) != string::npos) {
        pos = str.find(";", start);
        stack = str.substr(start, pos-start);
        stacks.push_back(stack);
        start = pos + 1;
    }

    stack = str.substr(start, str.size()-start);
    stacks.push_back(stack);

    return stacks;
}

vector<char> State::get_blocks(State s) {
    vector<char> blocks;

    for (int i=0; i<s.get_key().length(); ++i) {
        if (s.get_key()[i] != ';') {
            blocks.push_back(s.get_key()[i]);
        }
    }

    return blocks;
}

float State::heuristic(State& goal) {
    // // trivial heuristic
    // return 0;


    // // default-ish heuristic?
    // int h=0;
    // for (int i=0; i<key.size(); ++i) {
    //     if (key[i] != goal.get_key()[i]) ++h;
    // }
    // return h;


    // my heuristic
    int h=0;

    vector<string> stacks_curr = get_stacks(*this);
    vector<string> stacks_goal = get_stacks(goal);
    vector<char> blocks = get_blocks(goal);
    
    for (int i=0; i<blocks.size(); ++i) {
        bool found = false;
        for (int j=0; j<num_stacks; ++j) {
            if (stacks_curr[j].find(blocks[i]) != string::npos && stacks_goal[j].find(blocks[i]) != string::npos) {
                found = true;
                break;
            }
        }
        if (!found) {
            // for (int k=0; k<num_stacks; ++k) {
            //     if (stacks_curr[k].find(blocks[i]) != string::npos) {
            //         int pos = stacks_curr[k].find(blocks[i]);
            //         h += stacks_curr[k].size() - pos + 1;
            //     }
            // }
            h += 1;
        }
    }
    
    string key_curr = " " + key + " ";
    string key_goal = " " + goal.get_key() + " ";
    
    string cmp_curr, cmp_goal;
    int pos_curr, pos_goal;
    
    for (int m=0; m<blocks.size(); ++m) {
        pos_curr = key_curr.find(blocks[m]);
        pos_goal = key_goal.find(blocks[m]);

        cmp_curr = key_curr.substr(pos_curr-1, 3);
        cmp_goal = key_goal.substr(pos_goal-1, 3);

        if (cmp_curr[0] != cmp_goal[0]) h += 2;
        if (cmp_curr[2] != cmp_goal[2]) h += 1;

        // if (cmp_curr[0] == cmp_goal[1] && cmp_curr[1] == cmp_goal[0]) h+=3;
        // if (cmp_curr[1] == cmp_goal[2] && cmp_curr[2] == cmp_goal[1]) h+=3;
    }
    
    return h;
}
