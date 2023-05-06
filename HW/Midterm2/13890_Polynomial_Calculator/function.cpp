#include <iostream>
#include <string>
#include <cmath>
#include "function.h"

using namespace std;

class Constant : public Function {
public:
    double value;
    Constant() = default;
    Constant(double x) : value(x) {}

    static Constant *create(double x) {
        return new Constant(x);
    }
    virtual double eval(double x) override {
        return value;
    }
};

class Variable : public Function {
public:
    string var;
    Variable() = default;
    Variable(string s) : var(s) {}

    static Variable *create(string s) {
        return new Variable(s);
    }
    virtual double eval(double x) override {
        return x;
    }
};

class Polynomial : public Function {
public:
    Function *base, *exp;
    Polynomial() = default;
    Polynomial(Function *a, Function *b) : base(a), exp(b) {}

    static Polynomial *create(Function *a, Function *b) {
        return new Polynomial(a, b);
    }
    virtual double eval(double x) override {
        return pow(base->eval(x), exp->eval(x));
    }
};

class Arithmetic : public Function {
public:
    Function *a, *b;
    char op;
    Arithmetic() = default;
    Arithmetic(Function *a, char op, Function *b) : a(a), op(op), b(b) {}

    static Arithmetic *create(Function *a, char op, Function *b) {
        return new Arithmetic(a, op, b);
    }
    virtual double eval(double x) override {
        double lhs = a->eval(x), rhs = b->eval(x);
        switch (op) {
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '*':
            return lhs * rhs;
        case '/':
            return lhs / rhs;
        default:
            return 0.0;
        }
    }
};

class Sin : public Function {
public:
    Function *a;
    Sin() = default;
    Sin(Function *a) : a(a) {}

    static Sin *create(Function *a) {
        return new Sin(a);
    }
    virtual double eval(double x) override {
        return sin(a->eval(x));
    }
};

class Cos : public Function {
public:
    Function *a;
    Cos() = default;
    Cos(Function *a) : a(a) {}

    static Cos *create(Function *a) {
        return new Cos(a);
    }
    virtual double eval(double x) override {
        return cos(a->eval(x));
    }
};

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
