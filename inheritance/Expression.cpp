#include <string>
#include "Expression.h"

Expression::Expression(){
}

Expression::~Expression(){
}

BinaryExpression::BinaryExpression(Expression* subexp1, Expression* subexp2) : exp1(subexp1), exp2(subexp2){
}
BinaryExpression::~BinaryExpression(){
}

UnaryExpression::UnaryExpression(Expression* subexp) : exp1(subexp){
}
UnaryExpression::~UnaryExpression(){
}

Number::Number(int n) : number(n){
}
Number::~Number(){
	number=0;
}

std::string Number::type() const{
    return "Number";
}

// When the expression variable reaches the base case being a number.
// This class will be called when this happens and returns a number.
int Number::evaluate() const{
    return number;
}

// Returns a number in string format
std::string Number::print() const{
    return std::to_string(number);
}

// Puts the local Expression variables in the BinaryExpression constructor, intialising
// my protected variables
Multiply::Multiply(Expression* subexp1, Expression* subexp2) : BinaryExpression(subexp1,subexp2){
}

Multiply::~Multiply(){
    exp1 = nullptr; exp2 = nullptr;
}

std::string Multiply::type() const{
    return "Multiply";
}

// Recursively calls the evaluate function of both subexpressions until it gets to the
// base case, being a number (Number::evaluate).
int Multiply::evaluate() const{
    return exp1->evaluate() * exp2->evaluate();
}

// Prints the multiply format as: (subexp1*subexp2) where it's the whole expression
std::string Multiply::print() const{
    return "("+exp1->print()+"*"+exp2->print()+")";
}

// Contructor for Add, follows the same principles as Multiply constructor
Add::Add(Expression* subexp1, Expression* subexp2) : BinaryExpression(subexp1,subexp2){
}

Add::~Add(){
    exp1 = nullptr; exp2 = nullptr;
}

std::string Add::type() const{
    return "Add";
}

// Same principle as Multiple::evaluate, but adds the expressions
int Add::evaluate() const{
    return exp1->evaluate() + exp2->evaluate();
}

// Same principle as Multiple::print but has a + instead of a * e.g. (subexp1+subexp2)
std::string Add::print() const{
    return "("+exp1->print()+"+"+exp2->print()+")";
}

// Constructor for Abs, which puts the local variable into the protected variable
// in UnaryExpression
Abs::Abs(Expression* subexp) : UnaryExpression(subexp) {
}

Abs::~Abs(){
    exp1 = nullptr;
}

std::string Abs::type() const{
    return "Abs";
}

// Recursively calls evaluate on the expression. If the evaluated method is ever negative
// then we multiply it by -1 to turn it into a positive value.
int Abs::evaluate() const{
    if(exp1->evaluate() < 0) {
        return exp1->evaluate()*-1;
    } else {
        return exp1->evaluate();
    }
}

// Prints Abs(expression)
std::string Abs::print() const{
    return "Abs("+exp1->print()+")";
}

// Same principle as Abs constructor
Square::Square(Expression* subexp) : UnaryExpression(subexp){
}

Square::~Square(){
    exp1 = nullptr;
}

std::string Square::type() const{
    return "Square";
}

// Evaluates the expression to the final value then multiplies itself with the same function
int Square::evaluate() const{
    return (exp1->evaluate()*exp1->evaluate());
}

// Prints Square(expression)
std::string Square::print() const{
    return "Square("+exp1->print()+")";
}