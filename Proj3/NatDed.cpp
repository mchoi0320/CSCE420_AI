#include <iostream>
#include "parser.hpp"

Expr* ModusPonens(Expr* s1, Expr* s2) {
    try {
        if (s1->kind == ATOM && s2->kind == ATOM) throw RuleApplicationError("Cannot apply Modus Ponens without an implication");
        if (s1->kind == ATOM) swap(s1, s2);
        else {
            if (s1->sub.size() != 3) throw RuleApplicationError("Cannot apply Modus Ponens");
            if (s1->sub[0]->sym != string("implies")) {
                swap(s1, s2);
                if (s1->sub[0]->sym != string("implies")) throw RuleApplicationError("Cannot apply Modus Ponens without an implication");
                if (!Eq(s1->sub[1], s2)) throw RuleApplicationError("Cannot apply Modus Ponens");
                return s1->sub[2];
            }
        }
        if (!Eq(s1->sub[1], s2)) throw RuleApplicationError("Cannot apply Modus Ponens");
        return s1->sub[2];
    }
    catch (runtime_error& e) { cout << e.what() << endl; }
}

Expr* ImplicationElimination(Expr* s) {
    try {
        if (s->kind != LIST) throw RuleApplicationError("Cannot apply Implication Elimination to a symbol");
        if (s->sub[0]->sym != string("implies") || s->sub.size() != 3) throw RuleApplicationError("Cannot apply Implication Elimination without an implication");

        string tmp = "(or (not ";
        for (int i=0; i<2; ++i) {
            if (s->sub[i+1]->kind == LIST) tmp += s->sub[i+1]->toString();
            else tmp += s->sub[i+1]->sym;
            if (i == 0) tmp += ") ";
        }
        tmp += ")";
        Expr* e = new Expr(tmp);

        return e;
    }
    catch (runtime_error& e) { cout << e.what() << endl; }
}

Expr* AndElimination(Expr* s) {
    try {
        if (s->kind != LIST) throw RuleApplicationError("Cannot apply And Elimination to a symbol");
        if (s->sub[0]->sym != "and" || s->sub.size() < 3) throw RuleApplicationError("Cannot apply And Elimination without a conjunction");

        return s->sub[1];
    }
    catch (runtime_error& e) { cout << e.what() << endl; }
}

Expr* AndIntroduction(Expr* s1, Expr* s2) {
    string tmp = "(and ";
    if (s1->kind == LIST) tmp += s1->toString();
    else tmp += s1->sym;
    tmp += " ";
    if (s2->kind == LIST) tmp += s2->toString();
    else tmp += s2->sym;
    tmp += ")";
    Expr* e = new Expr(tmp);

    return e;
}

Expr* OrIntroduction(Expr* s1, Expr* s2) {
    string tmp = "(or ";
    if (s1->kind == LIST) tmp += s1->toString();
    else tmp += s1->sym;
    tmp += " ";
    if (s2->kind == LIST) tmp += s2->toString();
    else tmp += s2->sym;
    tmp += ")";
    Expr* e = parse(tmp);

    return e;
}

Expr* DoubleNegationElimination(Expr* s) {
    try {
        if (s->kind == ATOM) throw RuleApplicationError("Cannot apply Double Negation Elimination to a symbol");
        if (s->sub.size() != 2) throw RuleApplicationError("Cannot apply Double Negation Elimination");
        if (s->sub[1]->kind == ATOM) throw RuleApplicationError("Cannot apply Double Negation Elimination");
        if (s->sub[1]->sub.size() != 2) throw RuleApplicationError("Cannot apply Double Negation Elimination");
        if (s->sub[0]->sym != string("not") || !Eq(s->sub[0], s->sub[1]->sub[0])) throw RuleApplicationError("Cannot apply Double Negation Elimination");

        return s->sub[1]->sub[1];
    }
    catch (runtime_error& e) { cout << e.what() << endl; }
}

Expr* Resolution(Expr* s1, Expr* s2) {
    try {
        if (s1->kind != LIST || s2->kind != LIST) throw RuleApplicationError("Cannot apply Resolution without Or expressions");        
        if (s1->sub[0]->sym != string("or") || s2->sub[0]->sym != string("or")) throw RuleApplicationError("Cannot apply Resolution without Or expressions");
        if (s1->sub[1]->kind == LIST || s1->sub[2]->kind == LIST || s2->sub[1]->kind == LIST || s2->sub[2]->kind == LIST) {
            if (s1->sub[1]->kind == LIST && s1->sub[1]->sub[0]->sym == string("not") && s1->sub[1]->sub.size() == 2) {
                if (Eq(s1->sub[1]->sub[1], s2->sub[1])) {
                    string tmp = "(or ";
                    if (s1->sub[2]->kind == LIST) tmp += s1->sub[2]->toString();
                    else tmp += s1->sub[2]->sym;
                    tmp += " ";
                    if (s2->sub[2]->kind == LIST) tmp += s2->sub[2]->toString();
                    else tmp += s2->sub[2]->sym;
                    tmp += ")";
                    Expr* e = parse(tmp);

                    return e;
                }
                if (Eq(s1->sub[1]->sub[1], s2->sub[2])) {
                    string tmp = "(or ";
                    if (s1->sub[2]->kind == LIST) tmp += s1->sub[2]->toString();
                    else tmp += s1->sub[2]->sym;
                    tmp += " ";
                    if (s2->sub[1]->kind == LIST) tmp += s2->sub[1]->toString();
                    else tmp += s2->sub[1]->sym;
                    tmp += ")";
                    Expr* e = parse(tmp);

                    return e;
                }
            }
            if (s1->sub[2]->kind == LIST && s1->sub[2]->sub[0]->sym == string("not") && s1->sub[2]->sub.size() == 2) {
                if (Eq(s1->sub[2]->sub[1], s2->sub[1])) {
                    string tmp = "(or ";
                    if (s1->sub[1]->kind == LIST) tmp += s1->sub[1]->toString();
                    else tmp += s1->sub[1]->sym;
                    tmp += " ";
                    if (s2->sub[2]->kind == LIST) tmp += s2->sub[2]->toString();
                    else tmp += s2->sub[2]->sym;
                    tmp += ")";
                    Expr* e = parse(tmp);

                    return e;
                }
                if (Eq(s1->sub[2]->sub[1], s2->sub[2])) {
                    string tmp = "(or ";
                    if (s1->sub[1]->kind == LIST) tmp += s1->sub[1]->toString();
                    else tmp += s1->sub[1]->sym;
                    tmp += " ";
                    if (s2->sub[2]->kind == LIST) tmp += s2->sub[2]->toString();
                    else tmp += s2->sub[2]->sym;
                    tmp += ")";
                    Expr* e = parse(tmp);

                    return e;
                }
            }
            if (s2->sub[1]->kind == LIST && s2->sub[1]->sub[0]->sym == string("not") && s2->sub[1]->sub.size() == 2) {
                if (Eq(s2->sub[1]->sub[1], s1->sub[1])) {
                    string tmp = "(or ";
                    if (s2->sub[2]->kind == LIST) tmp += s2->sub[2]->toString();
                    else tmp += s2->sub[2]->sym;
                    tmp += " ";
                    if (s1->sub[2]->kind == LIST) tmp += s1->sub[2]->toString();
                    else tmp += s1->sub[2]->sym;
                    tmp += ")";
                    Expr* e = parse(tmp);

                    return e;
                }
                if (Eq(s2->sub[1]->sub[1], s1->sub[2])) {
                    string tmp = "(or ";
                    if (s2->sub[2]->kind == LIST) tmp += s2->sub[2]->toString();
                    else tmp += s2->sub[2]->sym;
                    tmp += " ";
                    if (s1->sub[1]->kind == LIST) tmp += s1->sub[1]->toString();
                    else tmp += s1->sub[1]->sym;
                    tmp += ")";
                    Expr* e = parse(tmp);

                    return e;
                }
            }
            if (s2->sub[2]->kind == LIST && s2->sub[2]->sub[0]->sym == string("not") && s2->sub[2]->sub.size() == 2) {
                if (Eq(s2->sub[2]->sub[1], s1->sub[1])) {
                    string tmp = "(or ";
                    if (s2->sub[1]->kind == LIST) tmp += s2->sub[1]->toString();
                    else tmp += s2->sub[1]->sym;
                    tmp += " ";
                    if (s1->sub[2]->kind == LIST) tmp += s1->sub[2]->toString();
                    else tmp += s1->sub[2]->sym;
                    tmp += ")";
                    Expr* e = parse(tmp);

                    return e;
                }
                if (Eq(s2->sub[2]->sub[1], s1->sub[2])) {
                    string tmp = "(or ";
                    if (s2->sub[1]->kind == LIST) tmp += s2->sub[1]->toString();
                    else tmp += s2->sub[1]->sym;
                    tmp += " ";
                    if (s1->sub[1]->kind == LIST) tmp += s1->sub[1]->toString();
                    else tmp += s1->sub[1]->sym;
                    tmp += ")";
                    Expr* e = parse(tmp);

                    return e;
                }
            }
        }
        else throw RuleApplicationError("Cannot apply Resolution without a negation");
    }
    catch (runtime_error& e) { cout << e.what() << endl; }
}

Expr* DeMorgan(Expr* s) {
    try {
        Expr* e;
        if (s->kind == ATOM) throw RuleApplicationError("Cannot apply De Morgan's Law to a symbol");
        if (s->sub[0]->sym == string("not") && s->sub.size() == 2) {
            if (s->sub[1]->kind == ATOM) throw RuleApplicationError("Cannot apply De Morgan's Law");
            if (s->sub[1]->sub.size() != 3) throw RuleApplicationError("Cannot apply De Morgan's Law");

            string tmp = "";

            if (s->sub[1]->sub[0]->sym == string("and")) tmp += "(or (not ";
            else if (s->sub[1]->sub[0]->sym == string("or")) tmp += "(and (not ";
            else throw RuleApplicationError("Cannot apply De Morgan's Law without a conjunction or disjunction");
            
            for (int i=0; i<2; ++i) {
                if (s->sub[1]->sub[i+1]->kind == LIST) tmp += s->sub[1]->sub[i+1]->toString();
                else tmp += s->sub[1]->sub[i+1]->sym;
                if (i == 0) tmp += ") (not ";
            }
            tmp += "))";
            e = new Expr(tmp);

            return e;
        }
        else if (s->sub.size() == 3) {
            if (s->sub[0]->sym != string("and")) {
                if (s->sub[0]->sym != string("or")) throw RuleApplicationError("Cannot apply De Morgan's Law without a conjunction");
            }
            if (s->sub[1]->kind == ATOM || s->sub[2]->kind == ATOM) throw RuleApplicationError("Cannot apply De Morgan's Law without negated expressions");
            if (s->sub[1]->sub[0]->sym == string("not") && s->sub[1]->sub.size() == 2 && s->sub[2]->sub[0]->sym == string("not") && s->sub[2]->sub.size() == 2) {
                string tmp = "(not ";

                if (s->sub[0]->sym == string("and")) tmp += "(or ";
                else tmp += "(and ";
                
                for (int i=0; i<2; ++i) {
                    if (s->sub[i+1]->sub[1]->kind == LIST) tmp += s->sub[i+1]->sub[1]->toString();
                    else tmp += s->sub[i+1]->sub[1]->sym;
                    if (i == 0) tmp += " ";
                }
                tmp += "))";
                e = new Expr(tmp);

                return e;
            }
            else throw RuleApplicationError("Cannot apply De Morgan's Law without negated expressions");
        }
        else throw RuleApplicationError("Cannot apply De Morgan's Law without a negation");
    }
    catch (runtime_error& e) { cout << e.what() << endl; }
}

Expr* Commutative(Expr* s) {
    try {
        if (s->kind == ATOM) throw RuleApplicationError("Cannot apply Commutative Law to a symbol");
        if (s->sub[0]->sym == string("implies")) throw RuleApplicationError("Cannot apply Commutative Law to an implication");
        if (s->sub.size() != 3) throw RuleApplicationError("Cannot apply Commutative Law");

        string tmp = "";
        
        if (s->sub[0]->sym == string("and")) tmp += "(and ";
        else if (s->sub[0]->sym == string("or")) tmp += "(or ";

        for (int i=2; i>0; --i) {
            if (s->sub[i]->kind == LIST) tmp += s->sub[i]->toString();
            else tmp += s->sub[i]->sym;     
            if (i == 2) tmp += " ";
        }
        tmp += ")";
        Expr* e = parse(tmp);

        return e;
    }
    catch (runtime_error& e) { cout << e.what() << endl; }
}

Expr* Implication(Expr* s) {
    try {
        if (s->kind == ATOM) throw RuleApplicationError("Cannot apply Implication to a symbol");
        if (s->sub[0]->sym == string("implies")) throw RuleApplicationError("Already an implication");
        if (s->sub[0]->sym != string("or")) throw RuleApplicationError("Cannot apply Implication");
        if (s->sub.size() != 3) throw RuleApplicationError("Cannot apply Implication");
        if (s->sub[1]->sub[0]->sym != string("not")) throw RuleApplicationError("Cannot apply Implication");

        string tmp = "(implies ";
        if (s->sub[1]->sub[1]->kind == LIST) tmp += s->sub[1]->sub[1]->toString();
        else tmp += s->sub[1]->sub[1]->sym;
        tmp += " ";
        if (s->sub[2]->kind == LIST) tmp += s->sub[2]->toString();
        else tmp += s->sub[2]->sym;
        tmp += ")";
        Expr* e = parse(tmp);

        return e;
    }
    catch (runtime_error& e) { cout << e.what() << endl; }
}

Expr* DisjunctiveSyllogism(Expr* s1, Expr* s2) {
    try {
        if (s1->kind == ATOM || s2->kind == ATOM) throw RuleApplicationError("Cannot apply Disjunctive Syllogism without expressions");

        if (s1->sub[0]->sym == "not") swap(s1, s2);
        if (s1->sub[0]->sym != "or") throw RuleApplicationError("Cannot apply Disjunctive Syllogism");

        if (Eq(s1->sub[1], s2->sub[1])) return s1->sub[2];
        if (Eq(s1->sub[2], s2->sub[1])) return s1->sub[1];
    }
    catch (runtime_error& e) { cout << e.what() << endl; }
}
