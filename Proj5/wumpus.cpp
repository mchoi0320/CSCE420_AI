#include <iostream>
#include <set>
using namespace std;

int main(int argc, char** argv) {
    int n = atoi(argv[1]);

    cout << "### Coordinate System of Wumpus World ###\n";
    for (int i=n; i>0; i--) {
        cout << "# ";
        for (int j=1; j<n+1; j++) {
            cout << "(" << j << "," << i << ") ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "# rooms adjacent to a pit will have a breeze\n";
    for (int i=n; i>0; i--) {
        for (int j=1; j<n+1; j++) {
            if (i+1 <= n) cout << "(or (not pit" << j << i << ") breeze" << j << i+1 << ")\n";
            if (i-1 > 0) cout << "(or (not pit" << j << i << ") breeze" << j << i-1 << ")\n";
            if (j+1 <= n) cout << "(or (not pit" << j << i << ") breeze" << j+1 << i << ")\n";
            if (j-1 > 0) cout << "(or (not pit" << j << i << ") breeze" << j-1 << i << ")\n";
        }
    }
    cout << endl;

    cout << "# rooms adjacent to the wumpus will have a stench\n";
    for (int i=n; i>0; i--) {
        for (int j=1; j<n+1; j++) {
            if (i+1 <= n) cout << "(or (not wumpus" << j << i << ") stench" << j << i+1 << ")\n";
            if (i-1 > 0) cout << "(or (not wumpus" << j << i << ") stench" << j << i-1 << ")\n";
            if (j+1 <= n) cout << "(or (not wumpus" << j << i << ") stench" << j+1 << i << ")\n";
            if (j-1 > 0) cout << "(or (not wumpus" << j << i << ") stench" << j-1 << i << ")\n";
        }
    }
    cout << endl;

    cout << "# if there is no breeze in a room, the adjacent rooms do not have a pit\n";
    for (int i=n; i>0; i--) {
        for (int j=1; j<n+1; j++) {
            if (i+1 <= n) cout << "(or breeze" << j << i << " (not pit" << j << i+1 << "))\n";
            if (i-1 > 0) cout << "(or breeze" << j << i << " (not pit" << j << i-1 << "))\n";
            if (j+1 <= n) cout << "(or breeze" << j << i << " (not pit" << j+1 << i << "))\n";
            if (j-1 > 0) cout << "(or breeze" << j << i << " (not pit" << j-1 << i << "))\n";
        }
    }
    cout << endl;

    cout << "# if there is no stench in a room, the adjacent rooms do not have a wumpus\n";
    for (int i=n; i>0; i--) {
        for (int j=1; j<n+1; j++) {
            if (i+1 <= n) cout << "(or stench" << j << i << " (not wumpus" << j << i+1 << "))\n";
            if (i-1 > 0) cout << "(or stench" << j << i << " (not wumpus" << j << i-1 << "))\n";
            if (j+1 <= n) cout << "(or stench" << j << i << " (not wumpus" << j+1 << i << "))\n";
            if (j-1 > 0) cout << "(or stench" << j << i << " (not wumpus" << j-1 << i << "))\n";
        }
    }
    cout << endl;

    cout << "# there is only one wumpus\n";
    set<string> one_wump;
    for (int i=n; i>0; i--) {
        for (int j=1; j<n+1; j++) {
            for (int a=n; a>0; a--) {
                for (int b=1; b<n+1; b++) {
                    if (i != a || j != b) {
                        string clause = "(or (not wumpus" + to_string(j) + to_string(i) + ") ";
                        clause += "(not wumpus" + to_string(b) + to_string(a) + "))";
                        one_wump.insert(clause);
                    }
                }
            }
        }
    }
    for (auto clause : one_wump) cout << clause << endl;
    cout << endl;

    cout << "# there is no wumpus or pit in any room that has already been visited\n";
    for (int i=n; i>0; i--) {
        for (int j=1; j<n+1; j++) {
            cout << "(or (not visited" << j << i << ") (not wumpus" << j << i << "))\n";
            cout << "(or (not visited" << j << i << ") (not pit" << j << i << "))\n";
        }
    }
    cout << endl;

    cout << "# a room is safe if it does not contain a wumpus or a pit\n";
    for (int i=n; i>0; i--) {
        for (int j=1; j<n+1; j++) {
            cout << "(or wumpus" << j << i << " safe" << j << i << ")\n";
            cout << "(or pit" << j << i << " safe" << j << i << ")\n";
        }
    }
}