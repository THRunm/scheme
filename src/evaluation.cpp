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

Value Let::eval(Assoc &env) {} // let expression

Value Lambda::eval(Assoc &env) {} // lambda expression

Value Apply::eval(Assoc &e) {} // for function calling

Value Letrec::eval(Assoc &env) {} // letrec expression

Value Var::eval(Assoc &e) {

} // evaluation of variable

Value Fixnum::eval(Assoc &e) {
    return Value(new Integer(n));
} // evaluation of a fixnum

Value If::eval(Assoc &e) {

} // if expression

Value True::eval(Assoc &e) {
    return Value(new Boolean(true));
} // evaluation of #t

Value False::eval(Assoc &e) {
    return Value(new Boolean(false));
} // evaluation of #f

Value Begin::eval(Assoc &e) {

} // begin expression

Value Quote::eval(Assoc &e) {


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

Value Unary::eval(Assoc &e) {} // evaluation of single-operator primitive

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
            Value re(new Boolean(&rand1.ptr ==&rand2.ptr));
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