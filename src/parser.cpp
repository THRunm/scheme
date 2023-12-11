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
    switch (reserved_words[id->s]) {
        case E_QUOTE:{
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for quote");
            Expr re(new Quote(stxs[1]));
            re->e_type=E_QUOTE;
            return re;
        }

    }
    switch (primitives[id->s]) {
        case E_EXIT:{
            Expr re(new Exit);
            re->e_type = E_EXIT;
            return re;
        }
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
        case E_LT:
        {
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for <");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr re=new Less(f1,f2);
            re->e_type = E_LT;
            return re;
        }
        case E_LE:
        {
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for <=");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr re=new LessEq(f1,f2);
            re->e_type = E_LE;
            return re;
        }
        case E_EQ:
        {
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for =");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr re=new Equal(f1,f2);
            re->e_type = E_EQ;
            return re;
        }
        case E_GE:
        {
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for >=");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr re=new GreaterEq(f1,f2);
            re->e_type = E_GE;
            return re;
        }
        case E_GT:
        {
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for >");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr re=new Greater(f1,f2);
            re->e_type = E_GT;
            return re;
        }
        case E_CONS:
        {
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for cons");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr re=new Cons(f1,f2);
            re->e_type = E_CONS;
            return re;
        }
        case E_NOT:
        {
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for not");
            Expr f1 = stxs[1]->parse(env);
            Expr re(new Not(f1));
            re->e_type = E_NOT;
            return re;
        }
        case E_CAR:
        {
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for car");
            Expr f1 = stxs[1]->parse(env);
            Expr re(new Car(f1));
            re->e_type = E_CAR;
            return re;
        }
        case E_CDR:
        {
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for cdr");
            Expr f1 = stxs[1]->parse(env);
            Expr re(new Cdr(f1));
            re->e_type = E_CDR;
            return re;
        }
        case E_EQQ:
        {
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for eq?");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr re(new IsEq(f1,f2));
            re->e_type = E_EQQ;
            return re;
        }
        case E_BOOLQ:
        {
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for boolean?");
            Expr f1 = stxs[1]->parse(env);
            Expr re(new IsBoolean(f1));
            re->e_type = E_BOOLQ;
            return re;
        }
        case E_INTQ:
        {
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for fixnum?");
            Expr f1 = stxs[1]->parse(env);
            Expr re(new IsFixnum(f1));
            re->e_type = E_INTQ;
            return re;
        }
        case E_NULLQ:
        {
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for null?");
            Expr f1 = stxs[1]->parse(env);
            Expr re(new IsNull(f1));
            re->e_type = E_NULLQ;
            return re;
        }
        case E_PAIRQ:
        {
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for pair?");
            Expr f1 = stxs[1]->parse(env);
            Expr re(new IsPair(f1));
            re->e_type = E_PAIRQ;
            return re;
        }
        case E_PROCQ:
        {
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for procedure?");
            Expr f1 = stxs[1]->parse(env);
            Expr re(new IsProcedure(f1));
            re->e_type = E_PROCQ;
            return re;
        }


    }
}

#endif