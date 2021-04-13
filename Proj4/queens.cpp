#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Please enter the number of queens for the N-queens problem." << endl;
        exit(0);
    }
    int n = atoi(argv[1]);

    string queens[n][n];
    cout << "### Layout of Queens ###" << endl;
    for (int i=0; i<n; ++i) {
        cout << "# ";
        for (int j=0; j<n; ++j) {
            queens[i][j] = "Q" + to_string(j+1) + to_string(i+1);
            cout << queens[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "# there must be at least one queen in each row" << endl;
    for (int i=0; i<n; ++i) {
        cout << "(or "; 
        for (int j=0; j<n; ++j) {
            if (j != n-1) cout << queens[i][j] << " ";
            else cout << queens[i][j] << ")" << endl;
        }
    }
    cout << endl;

    cout << "# there must be at least one queen in each column" << endl;
    for (int i=0; i<n; ++i) {
        cout << "(or "; 
        for (int j=0; j<n; ++j) {
            if (j != n-1) cout << queens[j][i] << " ";
            else cout << queens[j][i] << ")" << endl;
        }
    }
    cout << endl;

    cout << "# no two queens may be in the same row" << endl;
    for (int i=0; i<n; ++i) {
        int start = 0;
        for (int k=0; k<n-1; ++k) {
            for (int j=start; j<n; ++j) {
                if (j != start) {
                    cout << "(or (not " << queens[i][start] << ") (not " << queens[i][j] << "))" << endl;
                }
            }
            start++;
        }
    }
    cout << endl;

    cout << "# no two queens may be in the same column" << endl;
    for (int i=0; i<n; ++i) {
        int start = 0;
        for (int k=0; k<n-1; ++k) {
            for (int j=start; j<n; ++j) {
                if (j != start) {
                    cout << "(or (not " << queens[start][i] << ") (not " << queens[j][i] << "))" << endl;
                }
            }
            start++;
        }
    }
    cout << endl;

    cout << "# no two queens may be in the same diagonal" << endl;
    string right_shifted_queens[n][(n*2)-1];
    int offset = 0;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<(n*2)-1; ++j) {
            if (j == offset) {
                int start = 0;
                for (int k=offset; k<offset+n; ++k) {
                    right_shifted_queens[i][k] = queens[i][start];
                    start++;
                }
                j += n - 1;
            }
            else {
                right_shifted_queens[i][j] = "---";
            }
        }
        offset++;
    }

    // for (int i=0; i<n; ++i) {
    //     for (int j=0; j<(n*2)-1; ++j) {
    //         cout << right_shifted_queens[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    string left_shifted_queens[n][(n*2)-1];
    offset = n - 1;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<(n*2)-1; ++j) {
            if (j == offset) {
                int start = 0;
                for (int k=offset; k<offset+n; ++k) {
                    left_shifted_queens[i][k] = queens[i][start];
                    start++;
                }
                j += n - 1;
            }
            else {
                left_shifted_queens[i][j] = "---";
            }
        }
        offset--;
    }    

    // for (int i=0; i<n; ++i) {
    //     for (int j=0; j<(n*2)-1; ++j) {
    //         cout << left_shifted_queens[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    for (int i=0; i<(n*2)-1; ++i) {
        int start = 0;
        for (int k=0; k<n-1; ++k) {
            for (int j=start; j<n; ++j) {
                if (right_shifted_queens[start][i] != "---" && right_shifted_queens[j][i] != "---") {
                    if (j != start) {
                        cout << "(or (not " << right_shifted_queens[start][i] << ") (not " << right_shifted_queens[j][i] << "))" << endl;
                    }
                }
                if (left_shifted_queens[start][i] != "---" && left_shifted_queens[j][i] != "---") {
                    if (j != start) {
                        cout << "(or (not " << left_shifted_queens[start][i] << ") (not " << left_shifted_queens[j][i] << "))" << endl;
                    }
                }
            }
            start++;
        }
    }
    cout << endl;

    // for (int i=0; i<n; ++i) {
    //     for (int j=0; j<n; ++j) {
    //         for (int a=0; a<n; ++a) {
    //             for (int b=0; b<n; ++b) {
    //                 if (i != j && a != b) {
    //                     if (abs(i-j) == abs(a-b)) {
    //                         cout << "(or (not " << queens[i][a] << ") (not " << queens[j][b] << "))" << endl;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
}