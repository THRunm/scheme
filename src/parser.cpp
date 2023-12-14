#ifndef PARSER 
#define PARSER

// parser of myscheme 

#include "RE.hpp"
#include "Def.hpp"
#include "syntax.hpp"
#include "expr.hpp"
#include <map>
#include "value.hpp"
#include <cstring>
#include <iostream>
#define mp make_pair
using std :: string;
using std :: vector;
using std :: pair;

vector<string> varna;
bool check(string s)
{
    for (int i=0;i<varna.size();i++)
    {
        if(varna[i]==s)return true;
    }
    return false;
}

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
//    if(primitives.find(s)!=primitives.end())
//    {
//        switch (primitives[s]) {
//            case E_QUOTE:
//            {
//                Expr re(new Quote(nullptr));
//                re->e_type = E_QUOTE;
//                return re;
//            }
//            case E_IF:
//            {
//                Expr re(new If(nullptr,nullptr,nullptr));
//                re->e_type = E_IF;
//                return re;
//            }
//            case E_BEGIN:
//            {
//                Expr re(new Begin(vector<Expr>()));
//                re->e_type = E_BEGIN;
//                return re;
//            }
//            case E_LAMBDA:
//            {
//                Expr re(new Lambda(vector<string>(),nullptr));
//                re->e_type = E_LAMBDA;
//                return re;
//            }
//            case E_LET:
//            {
//                Expr re(new Let(vector<pair<string,Expr>>(),nullptr));
//                re->e_type = E_LET;
//                return re;
//            }
//            case E_LETREC:
//            {
//                Expr re(new Letrec(vector<pair<string,Expr>>(),nullptr));
//                re->e_type = E_LETREC;
//                return re;
//            }
//            case E_EXIT:
//            {
//                Expr re(new Exit);
//                re->e_type = E_EXIT;
//                return re;
//            }
//            case E_PLUS:
//            {
//                Expr re(new Plus(nullptr,nullptr));
//                re->e_type = E_PLUS;
//                return re;
//            }
//            case E_MINUS:
//            {
//                Expr re(new Minus(nullptr,nullptr));
//                re->e_type = E_MINUS;
//                return re;
//            }
//            case E_MUL:
//            {
//                Expr re(new Mult(nullptr,nullptr));
//                re->e_type = E_MUL;
//                return re;
//            }
//            case E_LT:
//            {
//                Expr re(new Less(nullptr,nullptr));
//                re->e_type = E_LT;
//                return re;
//            }
//            case E_LE:
//            {
//                Expr re(new LessEq(nullptr,nullptr));
//                re->e_type = E_LE;
//                return re;
//            }
//            case E_EQ:
//            {
//                Expr re(new Equal(nullptr,nullptr));
//                re->e_type = E_EQ;
//                return re;
//            }
//            case E_GE:
//            {
//                Expr re(new GreaterEq(nullptr,nullptr));
//                re->e_type = E_GE;
//                return re;
//            }
//            case E_GT:
//            {
//                Expr re(new Greater(nullptr,nullptr));
//                re->e_type = E_GT;
//                return re;
//            }
//            case E_CONS:
//            {
//                Expr re(new Cons(nullptr,nullptr));
//                re->e_type = E_CONS;
//                return re;
//            }
//            case E_NOT:
//            {
//                Expr re(new Not(nullptr));
//                re->e_type = E_NOT;
//                return re;
//            }
//            case E_CAR:
//            {
//                Expr re(new Car(nullptr));
//                re->e_type = E_CAR;
//                return re;
//            }
//            case E_CDR:
//            {
//                Expr re(new Cdr(nullptr));
//                re->e_type = E_CDR;
//                return re;
//            }
//            case E_EQQ:
//            {
//                Expr re(new IsEq(nullptr,nullptr));
//                re->e_type = E_EQQ;
//                return re;
//            }
//            case E_BOOLQ:
//            {
//                Expr re(new IsBoolean(nullptr));
//                re->e_type = E_BOOLQ;
//                return re;
//            }
//            case E_INTQ:
//            {
//                Expr re(new IsFixnum(nullptr));
//                re->e_type = E_INTQ;
//                return re;
//            }
//            case E_NULLQ:
//            {
//                Expr re(new IsNull(nullptr));
//                re->e_type = E_NULLQ;
//                return re;
//            }
//            case E_PAIRQ:
//            {
//                Expr re(new IsPair(nullptr));
//                re->e_type = E_PAIRQ;
//                return re;
//            }
//            case E_PROCQ:
//            {
//                Expr re(new IsProcedure(nullptr));
//                re->e_type = E_PROCQ;
//                return re;
//            }
//            case E_SYMBOLQ:
//            {
//                Expr re(new IsSymbol(nullptr));
//                re->e_type = E_SYMBOLQ;
//                return re;
//            }
//            case E_VOID:
//            {
//                Expr re(new MakeVoid);
//                re->e_type = E_VOID;
//                return re;
//            }
//
//
//        }
//
//    }
//    else if(reserved_words.find(s)!=reserved_words.end())
//    {
//        switch (reserved_words[s]) {
//            case E_QUOTE:
//            {
//                Expr re(new Quote(nullptr));
//                re->e_type = E_QUOTE;
//                return re;
//            }
//            case E_IF:
//            {
//                Expr re(new If(nullptr,nullptr,nullptr));
//                re->e_type = E_IF;
//                return re;
//            }
//            case E_BEGIN:
//            {
//                Expr re(new Begin(vector<Expr>()));
//                re->e_type = E_BEGIN;
//                return re;
//            }
//            case E_LAMBDA:
//            {
//                Expr re(new Lambda(vector<string>(),nullptr));
//                re->e_type = E_LAMBDA;
//                return re;
//            }
//            case E_LET:
//            {
//                Expr re(new Let(vector<pair<string,Expr>>(),nullptr));
//                re->e_type = E_LET;
//                return re;
//            }
//            case E_LETREC:
//            {
//                Expr re(new Letrec(vector<pair<string,Expr>>(),nullptr));
//                re->e_type = E_LETREC;
//                return re;
//            }
//            case E_EXIT:
//            {
//                Expr re(new Exit);
//                re->e_type = E_EXIT;
//                return re;
//            }
//        }
//    }
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
    if(List * lis=dynamic_cast<List*>(stxs[0].get()))
    {
//        if(Identifier *id=dynamic_cast<Identifier *>(lis->stxs[0].get())) {
//            if (id->s == "lambda") {
//                vector<Expr> xs;
//                for (int i = 1; i < stxs.size(); ++i) {
//                    xs.push_back(stxs[i]->parse(env));
//                }
//
//                Expr re = new Apply(stxs[0]->parse(env), xs);
//                return re;
//            }
//
//        }
//        Expr re=lis->parse(env);
//        return re;
    }
    Expr f = stxs[0]->parse(env);
    if(Identifier *id = dynamic_cast<Identifier *>(stxs[0].get())){
    string s = id->s;
    ExprType et;
    if (primitives.find(s) != primitives.end())
        et = primitives[s];
    else if(check(s))
 { goto kop;}
    else if (reserved_words.find(s) != reserved_words.end())
        et = reserved_words[s];
    else { goto kop;}
    switch (et) {
        case E_QUOTE:{
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for quote");
            Expr re(new Quote(stxs[1]));
            re->e_type=E_QUOTE;
            return re;
        }
        case E_IF:
        {
            if (stxs.size() != 4)
                throw RuntimeError("wrong number of arguments for if");
            Expr f1 = stxs[1]->parse(env);
            Expr f2 = stxs[2]->parse(env);
            Expr f3 = stxs[3]->parse(env);
            Expr re(new If(f1,f2,f3));
            re->e_type = E_IF;
            return re;
        }
        case E_BEGIN:
        {
            if (stxs.size() < 2)
                throw RuntimeError("wrong number of arguments for begin");
            std::vector<Expr> es;
            for (int i = 1; i < stxs.size(); ++i)
                es.push_back(stxs[i]->parse(env));
            Expr re(new Begin(es));
            re->e_type = E_BEGIN;
            return re;
        }
        case E_LAMBDA:
        {
            if (stxs.size() != 3)
                goto kop;
                vector<string> params;
            int count=0;
            List *p=dynamic_cast<List*>(stxs[1].get());
            for (int i = 0; i < p->stxs.size(); ++i) {
                Identifier *id = dynamic_cast<Identifier *>(p->stxs[i].get());
                if(!check(id->s)){varna.push_back(id->s);
                count++;}
                params.push_back(id->s);
            }
            Expr body = stxs[2]->parse(env);
            for (int i=0;i<count;i++)varna.pop_back();
            Expr re=new Lambda(params,body);
            return re;
        }
        case E_LET:{
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for let");
            vector<pair<string,Expr>> bind;
            int count=0;
            vector<string>varnames;
            List *p=dynamic_cast<List*>(stxs[1].get());
            for (int i = 0; i < p->stxs.size(); ++i) {
                List *q=dynamic_cast<List*>(p->stxs[i].get());
                Identifier *id = dynamic_cast<Identifier *>(q->stxs[0].get());
                if(!check(id->s)){varnames.push_back(id->s);
                count++;}
                bind.push_back(mp(id->s,q->stxs[1]->parse(env)));
            }
            for(int i=0;i<count;i++)varna.push_back(varnames[i]);
            Expr body = stxs[2]->parse(env);
            for (int i=0;i<count;i++)varna.pop_back();
            Expr re=new Let(bind,body);
            return re;
        }
        case E_LETREC:{
            if (stxs.size() != 3)
                throw RuntimeError("wrong number of arguments for letrec");
            vector<pair<string,Expr>> bind;
            vector<string>varnames;
            int count=0;
            List *p=dynamic_cast<List*>(stxs[1].get());
            for (int i = 0; i < p->stxs.size(); ++i) {
                List *q=dynamic_cast<List*>(p->stxs[i].get());
                Identifier *id = dynamic_cast<Identifier *>(q->stxs[0].get());
                if(!check(id->s)){varnames.push_back(id->s);
                count++;}
                bind.push_back(mp(id->s,q->stxs[1]->parse(env)));
            }
            for(int i=0;i<count;i++)varna.push_back(varnames[i]);
            Expr body = stxs[2]->parse(env);
            for (int i=0;i<count;i++)varna.pop_back();
            Expr re=new Letrec(bind,body);
            return re;

        }
    }
    switch (et) {
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
            if (stxs.size() != 3) {
                throw RuntimeError("wrong number of arguments for =");
            }            Expr f1 = stxs[1]->parse(env);
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
        case E_SYMBOLQ:
        {
            if (stxs.size() != 2)
                throw RuntimeError("wrong number of arguments for symbol?");
            Expr f1 = stxs[1]->parse(env);
            Expr re(new IsSymbol(f1));
            re->e_type = E_SYMBOLQ;
            return re;
        }
        case E_VOID:{
            Expr re(new MakeVoid);
            re->e_type = E_VOID;
            return re;
        }
    }}
    kop:
std::vector<Expr> es;
for (int i = 1; i < stxs.size(); ++i)
    es.push_back(stxs[i]->parse(env));
Expr re(new Apply(f,es));
    return re;
}

#endif