#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "parser.hpp"
using namespace std;

typedef unordered_map<string, int> MODEL;
// Truth values:
// -1 = unassigned
//  0 = false
//  1 = true
MODEL create_model(vector<Expr*> clauses) {
    unordered_map<string, int> model;
    for (int i=0; i<clauses.size(); ++i) {
        for (int j=1; j<clauses[i]->sub.size(); ++j) {
            if (clauses[i]->sub[j]->kind == ATOM) {
                if (model.count(clauses[i]->sub[j]->sym) == 0) {
                    model[clauses[i]->sub[j]->sym] = -1;
                }
            }
            if (clauses[i]->sub[j]->kind == LIST) {
                if (model.count(clauses[i]->sub[j]->sub[1]->sym) == 0) {
                    model[clauses[i]->sub[j]->sub[1]->sym] = -1;
                }
            }
        }
    }

    // for (auto p : model) {
    //     cout << p.first << endl;
    // }

    return model;
}

vector<string> get_symbols(unordered_map<string, int> model) {
    vector<string> symbols;
    for (auto p : model) {
        symbols.push_back(p.first);
    }

    return symbols;
}

pair<int, int> check_clauses(vector<Expr*> clauses, MODEL model) {
    int clauses_satisfied = 0;
    for (int i=0; i<clauses.size(); ++i) {
        for (int j=1; j<clauses[i]->sub.size(); ++j) {
            if (clauses[i]->sub[j]->kind == ATOM) {
                if (model[clauses[i]->sub[j]->sym] == 1) {
                    clauses_satisfied++;
                    break;
                }
            }
            if (clauses[i]->sub[j]->kind == LIST) {
                if (model[clauses[i]->sub[j]->sub[1]->sym] == 0) {
                    clauses_satisfied++;
                    break;
                }
            }
        }
    }
    cout << "num clauses satisfied: " << clauses_satisfied << " out of " << clauses.size() << endl;

    int clauses_unsatisfied = 0;
    for (int i=0; i<clauses.size(); ++i) {
        int false_literals = 0;
        for (int j=1; j<clauses[i]->sub.size(); ++j) {
            if (clauses[i]->sub[j]->kind == ATOM) {
                if (model[clauses[i]->sub[j]->sym] == 0) false_literals++;
            }
            if (clauses[i]->sub[j]->kind == LIST) {
                if (model[clauses[i]->sub[j]->sub[1]->sym] == 1) false_literals++;
            }
        }
        if (false_literals == clauses[i]->sub.size() - 1) clauses_unsatisfied++;
    }

    // if (clauses_satisfied != clauses.size()) {
    //     for (auto p : model) {
    //         if (p.second == -1) return -1;
    //     }
    // }
    return make_pair(clauses_satisfied, clauses_unsatisfied);
}

pair<string, bool> find_unit_clause(vector<Expr*> clauses, MODEL model) {
    for (int i=0; i<clauses.size(); ++i) {
        int false_literals = 0;
        int true_literals = 0;
        for (int j=1; j<clauses[i]->sub.size(); ++j) {
            if (clauses[i]->sub[j]->kind == ATOM) {
                if (model[clauses[i]->sub[j]->sym] == 0) false_literals++;
                else if (model[clauses[i]->sub[j]->sym] == 1) true_literals++;
            }
            if (clauses[i]->sub[j]->kind == LIST) {
                if (model[clauses[i]->sub[j]->sub[1]->sym] == 1) false_literals++;
                else if (model[clauses[i]->sub[j]->sub[1]->sym] == 0) true_literals++;
            }
        }
        if (false_literals == clauses[i]->sub.size() - 2 && true_literals < 1) {
            for (int k=1; k<clauses[i]->sub.size(); ++k) {
                if (clauses[i]->sub[k]->kind == ATOM) {
                    if (model[clauses[i]->sub[k]->sym] == -1) return make_pair(clauses[i]->sub[k]->sym, false);
                }
                if (clauses[i]->sub[k]->kind == LIST) {
                    if (model[clauses[i]->sub[k]->sub[1]->sym] == -1) return make_pair(clauses[i]->sub[k]->sub[1]->sym, true);
                }            
            }
        }
    }

    return make_pair("no-unit-clause", false);
}

int cnt = 0;
bool DPLL(vector<Expr*> clauses, vector<string> symbols, MODEL model, bool unit, string prop = "") {
    cnt++;
    if (prop != "") {
        cout << "trying " << prop << "=" << model[prop] << "\n\n";
        prop = "";
    }

    cout << "model: ";
    for (auto p : model) {
        cout << p.first << "=";
        if (p.second == -1) cout << "? ";
        else if (p.second == 0) cout << "F ";
        else cout << "T ";
    }
    cout << endl;

    pair<int, int> clauses_status = check_clauses(clauses, model);
    if (clauses_status.first == clauses.size()) {
        cout << "\nsuccess!\n";
        cout << "number of DPLL calls = " << cnt;
        if (unit) cout << " (WITH unit-clause heuristic)\n";
        else cout << " (WITHOUT unit-clause heuristic)\n";
        cout << "here is a model:\n";
        for (auto p : model) {
            cout << p.first << " = ";
            if (p.second == 0) cout << "F\n";
            else cout << "T\n";
        }
        return true;
    }
    if (clauses_status.second > 0) {
        cout << "back-tracking...\n";
        return false;
    }

    if (unit) {
        pair<string, bool> p = find_unit_clause(clauses, model);
        if (p.first != "no-unit-clause") {
            vector<string>::iterator it = find(symbols.begin(), symbols.end(), p.first);
            symbols.erase(it);
            if (p.second) model[p.first] = 0;
            else model[p.first] = 1;
            cout << "forcing " << p.first << "=" << model[p.first] << "\n\n";
            return DPLL(clauses, symbols, model, unit);
        }
    }

    prop = *(symbols.begin());
    symbols.erase(symbols.begin());
    MODEL new_model1 = model, new_model2 = model;
    new_model1[prop] = 1;
    new_model2[prop] = 0;

    return (DPLL(clauses, symbols, new_model1, unit, prop) || DPLL(clauses, symbols, new_model2, unit, prop));
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Please provide a KB file name on the command line." << endl;
        exit(0);
    }

    vector<Expr*> clauses = load_kb(argv[1]);
    unordered_map<string, int> model = create_model(clauses);
    vector<string> symbols = get_symbols(model);
    sort(symbols.begin(), symbols.end(), greater<string>());

    bool unit = true;
    if (argc == 3) {
        string temp(argv[2]);
        if (temp != "-unit") {
            cout << "Invalid command-line argument: " << argv[2] << endl;
            exit(0);
        }
        unit = false;
    }

    for (int i=0; i<clauses.size(); ++i) {
        cout << clauses[i]->toString() << endl;
    }
    cout << endl;

    bool satisfiable = DPLL(clauses, symbols, model, unit);
    if (!satisfiable) {
        cout << "\nunsatisfiable\n";
        cout << "number of DPLL calls = " << cnt;
        if (unit) cout << " (WITH unit-clause heuristic)\n";
        else cout << " (WITHOUT unit-clause heuristic)\n";
    }
}