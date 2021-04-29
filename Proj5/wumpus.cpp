#include <iostream>
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
    for (int i=1; i<n+1; i++) {
        for (int j=1; j<n+1; j++) {
            if (j+1 <= n) cout << "(or (not pit" << i << j << ") breeze" << i << j+1 << ")\n";
            if (j-1 > 0) cout << "(or (not pit" << i << j << ") breeze" << i << j-1 << ")\n";
            if (i+1 <= n) cout << "(or (not pit" << i << j << ") breeze" << i+1 << j << ")\n";
            if (i-1 > 0) cout << "(or (not pit" << i << j << ") breeze" << i-1 << j << ")\n";
        }
    }
    cout << endl;

    cout << "# rooms adjacent to the wumpus will have a stench\n";
    for (int i=1; i<n+1; i++) {
        for (int j=1; j<n+1; j++) {
            if (j+1 <= n) cout << "(or (not wumpus" << i << j << ") stench" << 1 << j+1 << ")\n";
            if (j-1 > 0) cout << "(or (not wumpus" << i << j << ") stench" << i << j-1 << ")\n";
            if (i+1 <= n) cout << "(or (not wumpus" << i << j << ") stench" << i+1 << j << ")\n";
            if (i-1 > 0) cout << "(or (not wumpus" << i << j << ") stench" << i-1 << j << ")\n";
        }
    }
    cout << endl;

    // cout << "# if there is no breeze in a room, the adjacent rooms do not have a pit\n";
    // for (int i=n; i>0; i--) {
    //     for (int j=1; j<n+1; j++) {
    //         if (i+1 <= n) cout << "(or breeze" << j << i << " (not pit" << j << i+1 << "))\n";
    //         if (i-1 > 0) cout << "(or breeze" << j << i << " (not pit" << j << i-1 << "))\n";
    //         if (j+1 <= n) cout << "(or breeze" << j << i << " (not pit" << j+1 << i << "))\n";
    //         if (j-1 > 0) cout << "(or breeze" << j << i << " (not pit" << j-1 << i << "))\n";
    //     }
    // }
    // cout << endl;

    cout << "# if there is a breeze in a room, at least one of the adjacent rooms have a pit\n";
    for (int i=1; i<n+1; i++) {
        for (int j=1; j<n+1; j++) {
            cout << "(or (not breeze" << i << j << ")";
            if (j+1 <= n) cout << " pit" << i << j+1;
            if (j-1 > 0) cout << " pit" << i << j-1;
            if (i+1 <= n) cout << " pit" << i+1 << j;
            if (i-1 > 0) cout << " pit" << i-1 << j;
            cout << ")\n";
        }
    }
    cout << endl;

    // cout << "# if there is no stench in a room, the adjacent rooms do not have a wumpus\n";
    // for (int i=n; i>0; i--) {
    //     for (int j=1; j<n+1; j++) {
    //         if (i+1 <= n) cout << "(or stench" << j << i << " (not wumpus" << j << i+1 << "))\n";
    //         if (i-1 > 0) cout << "(or stench" << j << i << " (not wumpus" << j << i-1 << "))\n";
    //         if (j+1 <= n) cout << "(or stench" << j << i << " (not wumpus" << j+1 << i << "))\n";
    //         if (j-1 > 0) cout << "(or stench" << j << i << " (not wumpus" << j-1 << i << "))\n";
    //     }
    // }
    // cout << endl;

    // cout << "# if there is a stench in a room, one of the adjacent rooms have a wumpus\n";
    // for (int i=1; i<n+1; i++) {
    //     // for (int j=1; j<n+1; j++) {
    //     //     cout << "(or (not stench" << i << j << ")";
    //     //     if (j+1 <= n) cout << " wumpus" << i << j+1;
    //     //     if (j-1 > 0) cout << " wumpus" << i << j-1;
    //     //     if (i+1 <= n) cout << " wumpus" << i+1 << j;
    //     //     if (i-1 > 0) cout << " wumpus" << i-1 << j;
    //     //     cout << ")\n";
    //     // }

    //     for (int j=1; j<n+1; j++) {
    //         bool first = false, second = false, third = false, fourth = false;
            
    //         cout << "(or (not stench" << i << j << ")";
    //         if (j+1 <= n) { cout << " (not wumpus" << i << j+1 << ")"; first = true; }
    //         if (j-1 > 0) { cout << " (not wumpus" << i << j-1 << ")"; second = true; }
    //         if (i+1 <= n) { cout << " (not wumpus" << i+1 << j << ")"; third = true; }
    //         if (i-1 > 0) { cout << " (not wumpus" << i-1 << j << ")"; fourth = true; }
    //         cout << ")\n";

    //         if (first) {
    //             cout << "(or (not stench" << i << j << ")";
    //             if (j+1 <= n) cout << " (not wumpus" << i << j+1 << ")";
    //             if (j-1 > 0) cout << " wumpus" << i << j-1;
    //             if (i+1 <= n) cout << " wumpus" << i+1 << j;
    //             if (i-1 > 0) cout << " wumpus" << i-1 << j;
    //             cout << ")\n";
    //         }

    //         if (second) {
    //             cout << "(or (not stench" << i << j << ")";
    //             if (j+1 <= n) cout << " wumpus" << i << j+1;
    //             if (j-1 > 0) cout << " (not wumpus" << i << j-1 << ")";
    //             if (i+1 <= n) cout << " wumpus" << i+1 << j;
    //             if (i-1 > 0) cout << " wumpus" << i-1 << j;
    //             cout << ")\n";
    //         }
        
    //         if (third) {
    //             cout << "(or (not stench" << i << j << ")";
    //             if (j+1 <= n) cout << " wumpus" << i << j+1;
    //             if (j-1 > 0) cout << " wumpus" << i << j-1;
    //             if (i+1 <= n) cout << " (not wumpus" << i+1 << j << ")";
    //             if (i-1 > 0) cout << " wumpus" << i-1 << j;
    //             cout << ")\n";
    //         }

    //         if (fourth) {
    //             cout << "(or (not stench" << i << j << ")";
    //             if (j+1 <= n) cout << " wumpus" << i << j+1;
    //             if (j-1 > 0) cout << " wumpus" << i << j-1;
    //             if (i+1 <= n) cout << " wumpus" << i+1 << j;
    //             if (i-1 > 0) cout << " (not wumpus" << i-1 << j << ")";
    //             cout << ")\n";
    //         }
    //     }
    // }
    // cout << endl;

    cout << "# there is only one wumpus\n";
    for (int i=1; i<n+1; i++) {
        for (int j=1; j<n+1; j++) {
            for (int a=1; a<n+1; a++) {
                for (int b=1; b<n+1; b++) {
                    if (i != a || j != b) {
                        cout << "(or (not wumpus" << i << j << ") ";
                        cout << "(not wumpus" << a << b << "))\n";
                    }
                }
            }
        }
    }
    cout << endl;

    cout << "# there is no pit or wumpus in any room that has already been visited\n";
    for (int i=1; i<n+1; i++) {
        for (int j=1; j<n+1; j++) {
            cout << "(or (not visited" << i << j << ") (not pit" << i << j << "))\n";
            cout << "(or (not visited" << i << j << ") (not wumpus" << i << j << "))\n";
        }
    }
    cout << endl;

    cout << "# a room is safe if it does not contain a pit or a wumpus\n";
    for (int i=1; i<n+1; i++) {
        for (int j=1; j<n+1; j++) {
            cout << "(or pit" << i << j << " safe" << i << j << ")\n";
            cout << "(or wumpus" << i << j << " safe" << i << j << ")\n";
        }
    }
}