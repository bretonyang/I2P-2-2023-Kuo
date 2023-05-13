#include <iostream>
#include <string>
#include <cmath>
#include "function.h"

using namespace std;

class Constant : public Function {
public:
    double x;

    Constant(double x) : x(x) {}
    static Constant *create(double x) {
        return new Constant(x);
    }
    virtual Function *differential() override;
    virtual double eval(double x) override;
};

class Variable : public Function {
public:
    string var;

    Variable(string s) : var(s) {}
    static Variable *create(string s) {
        return new Variable(s);
    }
    virtual Function *differential() override;
    virtual double eval(double x) override;
};

class Polynomial : public Function {
public:
    Function *a, *b;

    Polynomial(Function *a, Function *b) : a(a), b(b) {}
    static Polynomial *create(Function *a, Function *b) {
        return new Polynomial(a, b);
    }
    virtual Function *differential() override;
    virtual double eval(double x) override;
};

class Arithmetic : public Function {
public:
    Function *a, *b;
    char op;

    Arithmetic(Function *a, char op, Function *b) : a(a), op(op), b(b) {}
    static Arithmetic *create(Function *a, char op, Function *b) {
        return new Arithmetic(a, op, b);
    }
    virtual Function *differential() override;
    virtual double eval(double x) override;
};

class Sin : public Function {
public:
    Function *a;

    Sin(Function *a) : a(a) {}
    static Sin *create(Function *a) {
        return new Sin(a);
    }
    virtual Function *differential() override;
    virtual double eval(double x) override;
};

class Cos : public Function {
public:
    Function *a;

    Cos(Function *a) : a(a) {}
    static Cos *create(Function *a) {
        return new Cos(a);
    }
    virtual Function *differential() override;
    virtual double eval(double x) override;
};

Function *Constant::differential() {
    return new Constant(0.0);
}
double Constant::eval(double val) {
    return x;
}

Function *Variable::differential() {
    return new Constant(1.0);
}
double Variable::eval(double val) {
    return val;
}

Function *Polynomial::differential() {
    double ex = b->eval(0.0);
    Function *coeff = new Constant(ex);
    Function *rhs = new Arithmetic(new Polynomial(a, new Constant(ex - 1)), '*', a->differential());
    return new Arithmetic(coeff, '*', rhs);
}
double Polynomial::eval(double val) {
    return pow(a->eval(val), b->eval(val));
}

Function *Arithmetic::differential() {
    Function *lhs, *rhs;
    Function *f, *g;
    char dif_op;
    switch (op) {
    case '+':
    case'-':
        lhs = a->differential();
        rhs = b->differential();
        dif_op = op;
        break;
    case '*':
        lhs = new Arithmetic(a, '*', b->differential());
        rhs = new Arithmetic(b, '*', a->differential());
        dif_op = '+';
        break;
    case '/':
        f = new Arithmetic(b, '*', a->differential());
        g = new Arithmetic(a, '*', b->differential());
        lhs = new Arithmetic(f, '-', g);
        rhs = new Polynomial(b, new Constant(2.0));
        dif_op = '/';
        break;
    }
    return new Arithmetic(lhs, dif_op, rhs);
}
double Arithmetic::eval(double val) {
    double lhs = a->eval(val);
    double rhs = b->eval(val);
    switch (op) {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '*':
        return lhs * rhs;
    case '/':
        return lhs / rhs;
    }
}

Function *Sin::differential() {
    return new Arithmetic(new Cos(a), '*', a->differential());
}
double Sin::eval(double val) {
    return sin(a->eval(val));
}

Function *Cos::differential() {
    Function *lhs = new Arithmetic(new Constant(-1.0), '*', new Sin(a));
    Function *rhs = a->differential();
    return new Arithmetic(lhs, '*', rhs);
}
double Cos::eval(double val) {
    return cos(a->eval(val));
}

Function* Function::parse(stringstream &ss){
    string s;
    ss >> s;
    if(s == "+" || s == "-" || s == "*" || s == "/"){
        Function *a = parse(ss), *b = parse(ss);
        Function *now = Arithmetic::create(a, s[0], b);
        return now;
    }else if(s[0] == 'x'){
        Function *now = Variable::create(s);
        return now;
    }else if(s == "**"){
        Function *a = parse(ss), *b = parse(ss);
        Function *now = Polynomial::create(a, b);
        return now;
    }else if(s == "sin"){
        Function *a = parse(ss);
        Function *now = Sin::create(a);
        return now;
    }else if(s == "cos"){
        Function *a = parse(ss);
        Function *now = Cos::create(a);
        return now;
    }else{
        Function *now = Constant::create(atoi(s.c_str()));
        return now;
    }
}
