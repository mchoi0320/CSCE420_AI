#include <string>
#include <fstream>
#include <iostream>
#include "parser.hpp"
#include "NatDed.hpp"
using namespace std;

int main(int argc, char** argv) {

    if (argc < 2) {
        // Testing Modus Ponens
        cout << "Testing Modus Ponens...\n";
        string s1 = "(and (not B) C)";
        string s2 = "(implies (and (not B) C) A)";
        cout << "[INPUTS] " << s1 << " | " << s2 << endl;
        Expr* e1 = parse(s1);
        Expr* e2 = parse(s2);
        cout << "[OUTPUT] " << ModusPonens(e1, e2)->toString() << endl << endl;
        delete e1, e2;


        // Testing Implication Elimination
        cout << "Testing Implication Elimination...\n";
        string s3 = "(implies A B)";
        cout << "[ INPUT] " << s3 << endl;
        Expr* e3 = parse(s3);
        cout << "[OUTPUT] " << ImplicationElimination(e3)->toString() << endl << endl;    
        delete e3;


        // Testing And Elimination
        cout << "Testing And Elimination...\n";
        string s4 = "(and (not A) B C)";
        cout << "[ INPUT] " << s4 << endl;
        Expr* e4 = parse(s4);
        cout << "[OUTPUT] " << AndElimination(e4)->toString() << endl << endl;    
        delete e4;


        // Testing And Introduction
        cout << "Testing And Introduction...\n";
        string s5 = "A";
        string s6 = "(or B C)";
        cout << "[INPUTS] " << s5 << " | " << s6 << endl;
        Expr* e5 = parse(s5);
        Expr* e6 = parse(s6);
        cout << "[OUTPUT] " << AndIntroduction(e5, e6)->toString() << endl << endl;    
        delete e5, e6;


        // Testing Or Introduction
        cout << "Testing Or Introduction...\n";
        string s7 = "(and A B)";
        string s8 = "C";
        cout << "[INPUTS] " << s7 << " | " << s8 << endl;
        Expr* e7 = parse(s7);
        Expr* e8 = parse(s8);
        cout << "[OUTPUT] " << OrIntroduction(e7, e8)->toString() << endl << endl;    
        delete e7, e8;


        // Testing Double Negation Elimination
        cout << "Testing Double Negation Elimination...\n";
        string s9 = "(not (not (or A B)))";
        cout << "[ INPUT] " << s9 << endl;
        Expr* e9 = parse(s9);
        cout << "[OUTPUT] " << DoubleNegationElimination(e9)->toString() << endl << endl;    
        delete e9;


        // Testing Resolution
        cout << "Testing Resolution...\n";
        string s10 = "(or A B)";
        string s11 = "(or (not A) C)";
        cout << "[INPUTS] " << s10 << " | " << s11 << endl;
        Expr* e10 = parse(s10);
        Expr* e11 = parse(s11);
        cout << "[OUTPUT] " << Resolution(e10, e11)->toString() << endl << endl;    


        // Testing De Morgan's Laws
        cout << "Testing De Morgan's Laws (1)...\n";
        string s12 = "(not (and A (not B)))";
        cout << "[ INPUT] " << s12 << endl;
        Expr* e12 = parse(s12);
        cout << "[OUTPUT] " << DeMorgan(e12)->toString() << endl << endl;    
        delete e12;

        cout << "Testing De Morgan's Laws (2)...\n";
        string s13 = "(not (or (not A) B))";
        cout << "[ INPUT] " << s13 << endl;
        Expr* e13 = parse(s13);
        cout << "[OUTPUT] " << DeMorgan(e13)->toString() << endl << endl;    
        delete e13;

        // Testing Commutative Law
        cout << "Testing Commutative Law...\n";
        cout << "[ INPUT] " << s11 << endl;
        cout << "[OUTPUT] " << Commutative(e11)->toString() << endl << endl;

        // Testing Implication
        cout << "Testing Implication...\n";
        cout << "[ INPUT] " << s11 << endl;
        cout << "[OUTPUT] " << Implication(e11)->toString() << endl << endl;

        // Testing Disjunctive Syllogism
        cout << "Testing Disjunctive Syllogism...\n";
        string s14 = "(not A)";
        cout << "[INPUTS] " << s10 << " | " << s14 << endl;
        Expr* e14 = parse(s14);
        cout << "[OUTPUT] " << DisjunctiveSyllogism(e10, e14)->toString() << endl << endl;
        delete e10, e11, e14;
    }

    else {
        vector<Expr*> KB = load_kb(argv[1]);

        KB.push_back(parse("O1Y"));
        KB.push_back(parse("L1W"));
        KB.push_back(parse("O2W"));
        KB.push_back(parse("L2Y"));
        KB.push_back(parse("O3Y"));
        KB.push_back(parse("L3B"));
        KB.push_back(ModusPonens(KB[23], KB[31]));
        KB.push_back(ModusPonens(KB[11], KB[32]));
        KB.push_back(DisjunctiveSyllogism(KB[33], KB[34]));
        KB.push_back(ModusPonens(KB[2], KB[35]));
        KB.push_back(ModusPonens(KB[21], KB[27]));
        KB.push_back(AndElimination(KB[36]));
        KB.push_back(DisjunctiveSyllogism(KB[37], KB[38]));
        KB.push_back(ModusPonens(KB[6], KB[39]));
        KB.push_back(AndElimination(KB[40]));
        KB.push_back(ModusPonens(KB[25], KB[29]));
        KB.push_back(DisjunctiveSyllogism(KB[42], KB[41]));

        string filename(argv[1]);
        filename.replace(filename.find(".kb"), 3, ".txt");
        ofstream file(filename.c_str());
        for (int i=0; i<KB.size(); ++i) {
            file << KB[i]->toString() << endl;
            delete KB[i];
        }
        file.close();
    }
}
