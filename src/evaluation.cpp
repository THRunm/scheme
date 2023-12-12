#include "Def.hpp"
#include "value.hpp"
#include "expr.hpp"
#include "RE.hpp"
#include "syntax.hpp"
#include <cstring>
#include <vector>
#include <map>

extern std :: map<std :: string, ExprType> primitives;
extern std :: map<std :: string, ExprType> reserved_words;

Value Let::eval(Assoc &env) {
    Assoc tmp=env;
        for(int i=0;i<bind.size();i++){
            Value re=bind[i].second->eval(tmp);
            tmp=extend(bind[i].first,re,tmp);
        }
    return body->eval(tmp);
} // let expression

Value Lambda::eval(Assoc &env) {
    Value re(new Closure(x,e,env));
    re->v_type = V_PROC;
    return re;
} // lambda expression

Value Apply::eval(Assoc &e) {
    if(Lambda *r1=dynamic_cast<Lambda*>(rator.get())){
    Assoc tmp=e;
    for (int i=0;i<r1->x.size();i++){
        Value re=rand[i]->eval(e);
        tmp= extend(r1->x[i],re,tmp);
    }
    return r1->e->eval(tmp);}
    else if(Var *r1=dynamic_cast<Var*>(rator.get())){
        Value t= find(r1->x,e);
        Closure *r2=dynamic_cast<Closure*>(t.get());
        Assoc tmp=e;
        for(int i=0;i<r2->parameters.size();i++)
        {
            Value re=rand[i]->eval(e);
            tmp=extend(r2->parameters[i],re,tmp);
        }
        return r2->e->eval(tmp);
    }
} // for function calling

Value Letrec::eval(Assoc &env) {
    Assoc tmp=env;
    for(int i=0;i<bind.size();i++){
        Value re=new Null();
        re->v_type=V_NULL;
        tmp=extend(bind[i].first,re,tmp);
    }
    Assoc tmp2=tmp;
    for (int i=0;i<bind.size();i++){
        Value re=bind[i].second->eval(tmp2);
        tmp2=extend(bind[i].first,re,tmp2);
    }
    return body->eval(tmp2);
} // letrec expression

Value Var::eval(Assoc &e) {
    for (AssocList *p = e.get(); p != nullptr; p = p->next.get()) {
        if (p->x == x) {
            return p->v;
        }
    }
}
     // evaluation of variable

Value Fixnum::eval(Assoc &e) {
    return Value(new Integer(n));
} // evaluation of a fixnum

Value If::eval(Assoc &e) {
    if (cond->eval(e)->v_type == V_BOOL)
    {
        Value f1 = cond->eval(e);
        Boolean *f2 = dynamic_cast<Boolean *>(f1.get());
        if(f2->b == true)
        {
            return this->conseq->eval(e);
        }
        else
        {
            return this->alter->eval(e);
        }

    }
    else
    {
        return conseq->eval(e);
    }
} // if expression

Value True::eval(Assoc &e) {
    return Value(new Boolean(true));
} // evaluation of #t

Value False::eval(Assoc &e) {
    return Value(new Boolean(false));
} // evaluation of #f

Value Begin::eval(Assoc &e) {
    if(es.size()==0){
        Value re=new Void();
        re->v_type=V_VOID;
        return re;
    }
    else{
        Value re=es[0]->eval(e);
        for(int i=1;i<es.size();i++){
            re=es[i]->eval(e);
        }
        return re;
    }
} // begin expression
Value makeList(Assoc &e,const std::vector<Syntax> &stxs,int i);
Value back(Assoc &e,const Syntax& u){
     if(List *p=dynamic_cast<List*>(u.get())){
        return makeList(e,p->stxs,0);
    }
    else if(Number *p=dynamic_cast<Number*>(u.get())){
        return IntegerV(p->n);
    }
    else if(Identifier *p=dynamic_cast<Identifier*>(u.get())){
        return SymbolV(p->s);
    }
    else if(TrueSyntax *p=dynamic_cast<TrueSyntax*>(u.get())){
        return BooleanV(true);
    }
    else if(FalseSyntax *p=dynamic_cast<FalseSyntax*>(u.get())){
        return BooleanV(false);
    }

    else{
        throw "error";
    }

}
Value makeList(Assoc &e,const std::vector<Syntax> &stxs,int i){
    if(stxs.size()==0||i==stxs.size()){
        return NullV();
    }
    else{
        return PairV(back(e,stxs[i]),makeList(e,stxs,i+1));
    }
}

Value Quote::eval(Assoc &e) {
    Value re=back(e,s);
    return re;
} // quote expression

Value MakeVoid::eval(Assoc &e) {
    Value re=new Void();
    re->v_type=V_VOID;
    return re;
} // (void)

Value Exit::eval(Assoc &e) {
    Exit *p = dynamic_cast<Exit *>(this);
    Value re = new Terminate;
    re->v_type = V_TERMINATE;
    return re;
} // (exit)

Value Binary::eval(Assoc &e) {
    Value re=this->evalRator(rand1->eval(e),rand2->eval(e));
    return re;
} // evaluation of two-operators primitive

Value Unary::eval(Assoc &e) {
    Value re=this->evalRator(rand->eval(e));
    return re;
} // evaluation of single-operator primitive

Value Mult::evalRator(const Value &rand1, const Value &rand2) {
    if(rand1->v_type == V_INT && rand2->v_type == V_INT)
    {
        Integer *r1 = dynamic_cast<Integer *>(rand1.get());
        Integer *r2 = dynamic_cast<Integer *>(rand2.get());
        Value re(new Integer(r1->n * r2->n));
        re->v_type = V_INT;
        return re;
    }
    else
    {
        throw "error";
    }
} // *

Value Plus::evalRator(const Value &rand1, const Value &rand2) {
    if(rand1->v_type == V_INT && rand2->v_type == V_INT)
    {
        Integer *r1 = dynamic_cast<Integer *>(rand1.get());
        Integer *r2 = dynamic_cast<Integer *>(rand2.get());
        Value re(new Integer(r1->n + r2->n));
        re->v_type = V_INT;
        return re;
    }
    else
    {
        throw "error";
    }
} // +

Value Minus::evalRator(const Value &rand1, const Value &rand2) {
    if(rand1->v_type == V_INT && rand2->v_type == V_INT)
    {
        Integer *r1 = dynamic_cast<Integer *>(rand1.get());
        Integer *r2 = dynamic_cast<Integer *>(rand2.get());
        Value re(new Integer(r1->n - r2->n));
        re->v_type = V_INT;
        return re;
    }
    else
    {
        throw "error";
    }
} // -

Value Less::evalRator(const Value &rand1, const Value &rand2) {
    if(rand1->v_type == V_INT && rand2->v_type == V_INT)
    {
        Integer *r1 = dynamic_cast<Integer *>(rand1.get());
        Integer *r2 = dynamic_cast<Integer *>(rand2.get());
        Value re(new Boolean(r1->n < r2->n));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        throw "error";
    }
} // <

Value LessEq::evalRator(const Value &rand1, const Value &rand2) {
    if(rand1->v_type == V_INT && rand2->v_type == V_INT)
    {
        Integer *r1 = dynamic_cast<Integer *>(rand1.get());
        Integer *r2 = dynamic_cast<Integer *>(rand2.get());
        Value re(new Boolean(r1->n <= r2->n));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        throw "error";
    }
} // <=

Value Equal::evalRator(const Value &rand1, const Value &rand2) {
    if(rand1->v_type == V_INT && rand2->v_type == V_INT)
    {
        Integer *r1 = dynamic_cast<Integer *>(rand1.get());
        Integer *r2 = dynamic_cast<Integer *>(rand2.get());
        Value re(new Boolean(r1->n == r2->n));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        throw "error";
    }
} // =

Value GreaterEq::evalRator(const Value &rand1, const Value &rand2) {
    if(rand1->v_type == V_INT && rand2->v_type == V_INT)
    {
        Integer *r1 = dynamic_cast<Integer *>(rand1.get());
        Integer *r2 = dynamic_cast<Integer *>(rand2.get());
        Value re(new Boolean(r1->n >= r2->n));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        throw "error";
    }
} // >=

Value Greater::evalRator(const Value &rand1, const Value &rand2) {
    if(rand1->v_type == V_INT && rand2->v_type == V_INT)
    {
        Integer *r1 = dynamic_cast<Integer *>(rand1.get());
        Integer *r2 = dynamic_cast<Integer *>(rand2.get());
        Value re(new Boolean(r1->n > r2->n));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        throw "error";
    }
} // >

Value IsEq::evalRator(const Value &rand1, const Value &rand2) {
    if(rand1->v_type ==rand2->v_type)
    {
        if(rand1->v_type == V_INT)
        {
            Integer *r1 = dynamic_cast<Integer *>(rand1.get());
            Integer *r2 = dynamic_cast<Integer *>(rand2.get());
            Value re(new Boolean(r1->n == r2->n));
            re->v_type = V_BOOL;
            return re;
        }
        else if(rand1->v_type == V_BOOL)
        {
            Boolean *r1 = dynamic_cast<Boolean *>(rand1.get());
            Boolean *r2 = dynamic_cast<Boolean *>(rand2.get());
            Value re(new Boolean(r1->b == r2->b));
            re->v_type = V_BOOL;
            return re;
        }
        else{
            ValueBase *i=&*(rand1.get());
            ValueBase *j=&*(rand2.get());
            Value re(new Boolean(i == j));
            return re;
        }
    }
    else
    {
        Value re(new Boolean(false));
        re->v_type = V_BOOL;
        return re;
    }

} // eq?

Value Cons::evalRator(const Value &rand1, const Value &rand2) {
    Value re(new Pair(rand1,rand2));
    re->v_type = V_PAIR;
    return re;
} // cons

Value IsBoolean::evalRator(const Value &rand) {
    if(rand->v_type == V_BOOL)
    {
        Value re(new Boolean(true));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        Value re(new Boolean(false));
        re->v_type = V_BOOL;
        return re;
    }
} // boolean?

Value IsFixnum::evalRator(const Value &rand) {
    if(rand->v_type == V_INT)
    {
        Value re(new Boolean(true));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        Value re(new Boolean(false));
        re->v_type = V_BOOL;
        return re;
    }
} // fixnum?

Value IsNull::evalRator(const Value &rand) {
    if(rand->v_type == V_NULL)
    {
        Value re(new Boolean(true));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        Value re(new Boolean(false));
        re->v_type = V_BOOL;
        return re;
    }
} // null?

Value IsPair::evalRator(const Value &rand) {
    if(rand->v_type == V_PAIR)
    {
        Value re(new Boolean(true));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        Value re(new Boolean(false));
        re->v_type = V_BOOL;
        return re;
    }
} // pair?

Value IsProcedure::evalRator(const Value &rand) {
    if(rand->v_type == V_PROC)
    {
        Value re(new Boolean(true));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        Value re(new Boolean(false));
        re->v_type = V_BOOL;
        return re;
    }
} // procedure?

Value Not::evalRator(const Value &rand) {
    if(rand->v_type == V_BOOL)
    {
        Boolean *r = dynamic_cast<Boolean *>(rand.get());
        Value re(new Boolean(!r->b));
        re->v_type = V_BOOL;
        return re;
    }
    else
    {
        Value re(new Boolean(false));
        re->v_type = V_BOOL;
        return re;
    }
} // not

Value Car::evalRator(const Value &rand) {
    if(rand->v_type == V_PAIR)
    {
        Pair *r = dynamic_cast<Pair *>(rand.get());
        return r->car;
    }
    else
    {
        throw "error";
    }
} // car

Value Cdr::evalRator(const Value &rand) {
    if(rand->v_type == V_PAIR)
    {
        Pair *r = dynamic_cast<Pair *>(rand.get());
        return r->cdr;
    }
    else
    {
        throw "error";
    }
} // cdr