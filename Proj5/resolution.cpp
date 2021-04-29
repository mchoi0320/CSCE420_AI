#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <queue>
#include <vector>
#include "parser.hpp"
using namespace std;

#define MAX_ITERS 10000

class ResPair {
  public:
    int i, j, score;
    ResPair(int a, int b, int s) : i(a), j(b), score(s) {}
};

class Comparator {
  public:
    bool operator()(ResPair a, ResPair b) {
        return a.score > b.score;
    }
};

void print_KB(vector<Expr*> KB) {
    for (int i=0; i<KB.size(); i++) {
        string num = to_string(i) + ".";
        cout << left << setw(7) << num;
        cout << KB[i]->toString() << endl;
    }
    cout << endl;
}

Expr* negate_query(string s) {
    Expr* expr = parse(s);
    string str;
    if (expr->kind == ATOM) str = "(or (not " + expr->toString() + "))";
    else str = "(or " + expr->sub[1]->toString() + ")";
    Expr* query = parse(str);

    return query;
}

bool validate_clause(Expr* clause) {
    if (clause->kind == ATOM) return false;
    if (clause->sub[0]->sym != "or") return false;
    for (int i=1; i<clause->sub.size(); i++) {
        if (clause->sub[i]->kind == LIST) {
            if (clause->sub[i]->sub[0]->sym != "not") return false;
            if (clause->sub[i]->sub.size() > 2) return false;
        }
    }
    for (int i=1; i<clause->sub.size(); i++) {
        for (int j=1; j<clause->sub.size(); j++) {
            if (i != j) {
                if (clause->sub[i]->kind == ATOM && clause->sub[j]->kind == LIST) {
                    if (clause->sub[i]->sym == clause->sub[j]->sub[1]->sym) return false;
                }
                else if (clause->sub[i]->kind == LIST && clause->sub[j]->kind == ATOM) {
                    if (clause->sub[i]->sub[1]->sym == clause->sub[j]->sym) return false;
                }
            }
        }
    }

    return true;
}

bool resolvable(Expr* clause1, Expr* clause2) {
    for (int i=1; i<clause1->sub.size(); i++) {
        for (int j=1; j<clause2->sub.size(); j++) {
            if (clause1->sub[i]->kind == ATOM && clause2->sub[j]->kind == LIST) {
                if (clause1->sub[i]->sym == clause2->sub[j]->sub[1]->sym) return true;
            }
            else if (clause1->sub[i]->kind == LIST && clause2->sub[j]->kind == ATOM) {
                if (clause1->sub[i]->sub[1]->sym == clause2->sub[j]->sym) return true;
            }
        }
    }

    return false;
}

vector<string> matching_propositions(Expr* clause1, Expr* clause2) {
    vector<string> props;
    for (int i=1; i<clause1->sub.size(); i++) {
        for (int j=1; j<clause2->sub.size(); j++) {
            if (clause1->sub[i]->kind == ATOM && clause2->sub[j]->kind == LIST) {
                if (clause1->sub[i]->sym == clause2->sub[j]->sub[1]->sym) props.push_back(clause1->sub[i]->sym);
            }
            else if (clause1->sub[i]->kind == LIST && clause2->sub[j]->kind == ATOM) {
                if (clause1->sub[i]->sub[1]->sym == clause2->sub[j]->sym) props.push_back(clause2->sub[j]->sym);
            }
        }
    }

    return props;
}

Expr* resolve(Expr* clause1, Expr* clause2, string prop) {
    // string str = "(or ";
    // for (int i=1; i<clause1->sub.size(); i++) {
    //     if (clause1->sub[i]->kind == ATOM) {
    //         if (clause1->sub[i]->sym != prop) str += clause1->sub[i]->toString();
    //     }
    //     else {
    //         if (clause1->sub[i]->sub[1]->sym != prop) str += clause1->sub[i]->toString();
    //     }
    //     str += " ";
    // }
    // for (int i=1; i<clause2->sub.size(); i++) {
    //     if (clause2->sub[i]->kind == ATOM) {
    //         if (clause2->sub[i]->sym != prop) str += clause2->sub[i]->toString();
    //     }
    //     else {
    //         if (clause2->sub[i]->sub[1]->sym != prop) str += clause2->sub[i]->toString();
    //     }
    //     str += " ";
    // }
    // str += ")";

    vector<Expr*> literals;
    for (auto c : clause1->sub) {
        if (c->sym != "or") {
            if (c->kind == ATOM) {
                if (c->sym != prop) literals.push_back(c);
            }
            else {
                if (c->sub[1]->sym != prop) literals.push_back(c);
            }
        }
    }
    for (auto c : clause2->sub) {
        if (c->sym != "or") {
            if (c->kind == ATOM) {
                if (c->sym != prop) literals.push_back(c);
            }
            else {
                if (c->sub[1]->sym != prop) literals.push_back(c);
            }
        }
    }

    for (auto a = literals.begin(); a != literals.end(); a++) {
        for (auto b = literals.begin(); b != literals.end(); b++) {
            if (a != b) {
                if (Eq(*a, *b)) literals.erase(b--);
            }
        }
    }

    string str = "(or ";
    for (auto s : literals) str += s->toString() + " ";
    str += ")";
    Expr* new_expr = parse(str);

    return new_expr;
}

bool resolution(vector<Expr*> KB, Expr* query) {
    bool valid = true;
    for (int i=0; i<KB.size(); i++) {
        valid = validate_clause(KB[i]);
        if (!valid) return false;
    }
    KB.push_back(query);
    print_KB(KB);

    // queue<ResPair> q;
    priority_queue<ResPair, vector<ResPair>, Comparator> q;
    for (int j=0; j<KB.size(); j++) {
        for (int i=0; i<j; i++) {
            // if (resolvable(KB[i], KB[j])) q.push(ResPair(i, j, KB[i]->sub.size()-1 + KB[j]->sub.size()-1));
            if (resolvable(KB[i], KB[j])) q.push(ResPair(i, j, min(KB[i]->sub.size()-1, KB[j]->sub.size()-1)));
        }
    }

    int iter = 0;
    while (!q.empty() && iter++ < MAX_ITERS) {
        cout << "---< ITERATION " << iter-1 << " >---\n";
        cout << "Number of clauses: " << KB.size() << endl;

        // ResPair index = q.front();
        ResPair index = q.top();
        q.pop();
        Expr* clause1 = KB[index.i];
        Expr* clause2 = KB[index.j];
        cout << "Resolving clauses " << index.i << " & " << index.j << ": ";
        cout << clause1->toString() << " , " << clause2->toString() << endl;

        vector<string> props = matching_propositions(clause1, clause2);
        // if (props.size() > 1) {
        //     cout << "More than one opposite literal was found between the two clauses.\n";
        //     cout << "Skipping...\n\n";
        //     continue;
        // }
        // else {
        for (auto p : props) {
            Expr* resolvent = resolve(clause1, clause2, props[0]);
            cout << "Resolvent = " << resolvent->toString() << endl;
            
            if (resolvent->toString() == "(or)") return true;
            
            bool exists = false;
            for (auto clause : KB) {
                if (Eq(clause, resolvent)) {
                    exists = true;
                    break;
                }
            }
            // if (exists) {
            if (!validate_clause(resolvent) || exists) {
                cout << "The resolvent is an invalid clause or already exists in the KB.\n\n";
                // cout << "The resolvent already exists in the KB.\n\n";
                continue;
            }

            for (int i=0; i<KB.size(); i++) {
                // if (resolvable(KB[i], resolvent)) q.push(ResPair(i, KB.size(), KB[i]->sub.size()-1 + resolvent->sub.size()-1));
                if (resolvable(KB[i], resolvent)) q.push(ResPair(i, KB.size(), min(KB[i]->sub.size()-1, resolvent->sub.size()-1)));
            }
            KB.push_back(resolvent);
            string num = to_string(KB.size()-1) + ".";
            cout << left << setw(7) << num;
            cout << resolvent->toString() << endl << endl;
        }
    }

    return false;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Please enter the KB file name and the query into the command line in said order.\n";
        exit(0);        
    }
    if (argc < 3) {
        cout << "Please enter both the KB file name and the query into the command line in said order.\n";
        exit(0);
    }

    string file(argv[1]);
    vector<Expr*> KB = load_kb(file);
    string orig(argv[2]);
    Expr* query = negate_query(orig);

    // unit testing...
    // cout << resolvable(KB[0], KB[1]) << endl;   // 0
    // cout << resolvable(KB[0], KB[3]) << endl;   // 1
    // vector<string> props = matching_propositions(KB[0], KB[3]);
    // for (auto p : props) cout << p << endl;
    // cout << resolve(KB[0], KB[3], props[0])->toString() << endl;

    if (file == "sammys.cnf") {
        KB.push_back(parse("(or O1Y)"));
        KB.push_back(parse("(or L1W)"));
        KB.push_back(parse("(or O2W)"));
        KB.push_back(parse("(or L2Y)"));
        KB.push_back(parse("(or O3Y)"));
        KB.push_back(parse("(or L3B)"));
    }
    else if (file == "wumpus.cnf") {
        KB.push_back(parse("(or visited14)"));
        KB.push_back(parse("(or (not breeze14))"));
        KB.push_back(parse("(or (not stench14))"));
        KB.push_back(parse("(or (not pit14))"));
        KB.push_back(parse("(or (not wumpus14))"));

        KB.push_back(parse("(or visited24)"));
        KB.push_back(parse("(or breeze24)"));
        KB.push_back(parse("(or (not stench24))"));
        KB.push_back(parse("(or (not pit24))"));
        KB.push_back(parse("(or (not wumpus24))"));

        KB.push_back(parse("(or visited34)"));
        KB.push_back(parse("(or (not breeze34))"));
        KB.push_back(parse("(or stench34)"));
        KB.push_back(parse("(or (not pit34))"));
        KB.push_back(parse("(or (not wumpus34))"));

        KB.push_back(parse("(or visited44)"));
        KB.push_back(parse("(or (not breeze44))"));
        KB.push_back(parse("(or (not stench44))"));
        KB.push_back(parse("(or (not pit44))"));
        KB.push_back(parse("(or (not wumpus44))"));

        KB.push_back(parse("(or visited13)"));
        KB.push_back(parse("(or breeze13)"));
        KB.push_back(parse("(or (not stench13))"));
        KB.push_back(parse("(or (not pit13))"));
        KB.push_back(parse("(or (not wumpus13))"));

        KB.push_back(parse("(or visited12)"));
        KB.push_back(parse("(or (not breeze12))"));
        KB.push_back(parse("(or (not stench12))"));
        KB.push_back(parse("(or (not pit12))"));
        KB.push_back(parse("(or (not wumpus12))"));

        KB.push_back(parse("(or visited22)"));
        KB.push_back(parse("(or breeze22)"));
        KB.push_back(parse("(or (not stench22))"));
        KB.push_back(parse("(or (not pit22))"));
        KB.push_back(parse("(or (not wumpus22))"));

        KB.push_back(parse("(or visited32)"));
        KB.push_back(parse("(or (not breeze32))"));
        KB.push_back(parse("(or stench32)"));
        KB.push_back(parse("(or (not pit32))"));
        KB.push_back(parse("(or (not wumpus32))"));

        KB.push_back(parse("(or visited42)"));
        KB.push_back(parse("(or breeze42)"));
        KB.push_back(parse("(or (not stench42))"));
        KB.push_back(parse("(or (not pit42))"));
        KB.push_back(parse("(or (not wumpus42))"));
    }

    if (resolution(KB, query)) cout << "\nSuccess! An empty clause was derived, so " << orig << " is entailed." << endl;
    else cout << "Failure!" << endl;
}
