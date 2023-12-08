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
    return ptr -> parse(env);
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
    if(stxs.size()==0){
        Expr re(new MakeVoid);
        re->e_type = E_VOID;
        return re;
    }
    Identifier *id = dynamic_cast<Identifier *>(stxs[0].get());
    switch (primitives[id->s]) {
        case E_PLUS:
        {
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for +");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr re=new Plus(f1,f2);
            re->e_type = E_PLUS;
            return re;
        }
        case E_MINUS:
        {
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for -");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr re=new Minus(f1,f2);
            re->e_type = E_MINUS;
            return re;
        }
        case E_MUL:
        {
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for *");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr re=new Mult(f1,f2);
            re->e_type = E_MUL;
            return re;
        }
    }
}

#endif