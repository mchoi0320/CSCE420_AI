#include "parser.hpp"

Expr* ModusPonens(Expr*, Expr*);

Expr* ImplicationElimination(Expr*);

Expr* AndElimination(Expr*);

Expr* AndIntroduction(Expr*, Expr*);

Expr* OrIntroduction(Expr*, Expr*);

Expr* DoubleNegationElimination(Expr*);

Expr* Resolution(Expr*, Expr*);

Expr* DeMorgan(Expr*);

Expr* Commutative(Expr*);

Expr* Implication(Expr*);

Expr* DisjunctiveSyllogism(Expr*, Expr*);
