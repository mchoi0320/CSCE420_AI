#include <iostream>

#include "State.h"

using namespace std;

void State::print() {
    for (int i=0; i<key.length(); i++) {
        if (key[i] == ';') cout << endl;
        else cout << key[i];
    }
    cout << endl;
}

bool State::match(State* s) {
    return (key == s->get_key());
}

string State::hash() {
    string str = "";
    for (int i=0; i<num_stacks; i++) {
        for (int j=0; j<curr[i].size(); j++) str += curr[i][j];
        if (i != num_stacks-1) str += ';';
    }

    return str;
}

vector<State*> State::successors() {
    vector<State*> moves;

    for (int i=0; i<num_stacks; i++) {
        if (!curr[i].empty()) {
            for (int j=0; j<num_stacks; j++) {
                if (i != j) {
                    vector<vector<char> > temp = curr;
                    temp[j].push_back(temp[i][temp[i].size()-1]);
                    temp[i].erase(temp[i].end()-1);

                    // State move(temp, num_stacks);
                    State* move = new State(temp, num_stacks);
                    moves.push_back(move);
                }
            }
        }
    }

    return moves;
}