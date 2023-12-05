#ifndef PARSER 
#define PARSER

// parser of myscheme 

#include "RE.hpp"
#include "Def.hpp"
#include "syntax.hpp"
#include "expr.hpp"
#include <map>
#include <cstring>
#include <iostream>
#define mp make_pair
using std :: string;
using std :: vector;
using std :: pair;



extern std :: map<std :: string, ExprType> primitives;
extern std :: map<std :: string, ExprType> reserved_words;

Expr Syntax :: parse(Assoc &env) {

}

Expr Number :: parse(Assoc &env) {
   Expr re(new Fixnum(n));
   re->e_type = E_FIXNUM;
    return re;
}
Expr Identifier :: parse(Assoc &env) {
    Expr re(new Var(s));
    re->e_type = E_VAR;
    return re;
}

Expr TrueSyntax :: parse(Assoc &env) {
    Expr re(new True);
    re->e_type = E_TRUE;
    return re;
}

Expr FalseSyntax :: parse(Assoc &env) {
    Expr re(new False);
    re->e_type = E_FALSE;
    return re;
}

Expr List :: parse(Assoc &env) {


}

#endif