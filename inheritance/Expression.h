#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>

using std::string;

// In this exercise you will implement storing and evaluation 
// of simple arithmetic expressions using inheritance.
// 
// The hierarchy of expressions is:
//
//                  				Expression
//                       				 |
//             --------------------------------------------------
//             |                         |                      |
//        BinaryExpression              Number              UnaryExpression
//             |                                                |
//  ------------------------                            ----------------
//  |                      |                            |              |
// Multiply               Add                          Square         Abs
//
//
// Number represents expressions that are integer values,
// Multiply represents multiplication of two Expressions,
// Add represents sum of two Expressions, and
// Abs represents the absolute value of an Expression.         
// All expressions should support functions:
// type : return the name of the class
// print : return a string version of the entire expression
//         more details below
// evaluate : return the result of evaluating the expression
// The result of evaluating an expression is an integer.
//
// As in Part 1, you should add the virtual keyword where appropriate
// and then implement the functions where they are most appropriate.
// Expression, BinaryExpression, and UnaryExpression could be  abstract 
// classes but all other classes should be concrete classes.



class Expression {
public:
	Expression();
	virtual ~Expression();

	// Functions supported by all types of Expression:
	
	// Returns the result of evaluating the expression.
	virtual int evaluate() const=0;
	
	// Prints the expression.
	// You should NOT introduce extra spaces or new lines.
	// The brackets and the corresponding operator are part
	// of the output format and do not depend on the 
	// contents of the expression. Required format:
	//
	// Multiply: 
	// (subexp*subexp)
	//           
	// Add:
	// (subexp+subexp)
	//     
	// Abs:
	// Abs(subexp)
	//    
	// Square:
	// Square(subexp)
	//	
	// Number, where n is its value:
	// n
	virtual std::string print() const=0;

	// Returns the name of the class:
	// Multiply, Add, Number, Square or Abs
	virtual std::string type() const=0;
	
protected:
private:
};


class BinaryExpression : public Expression {
public:
	BinaryExpression() = delete;
	BinaryExpression(Expression* subexp1, Expression* subexp2);
	virtual ~BinaryExpression();

	// We make these inherited methods virtual as we are not implementing these into 
	// Expression.cpp file
	virtual int evaluate() const=0;
	virtual std::string type() const=0;
	virtual std::string print() const=0;
protected:

	// These variables are placed in protected as the child classes will need to use these
	// variables in their evaluation methods when recursively called.
	Expression* exp1;
	Expression* exp2;
private:
};

class UnaryExpression : public Expression {
public:
	UnaryExpression() = delete;
	UnaryExpression(Expression* subexp);
	virtual ~UnaryExpression();  	

	// Same with BinaryExpression methods, we do not need to implement these as well.
	virtual int evaluate() const=0;
	virtual std::string type() const=0;
	virtual std::string print() const=0;
protected:

	// The same reason from putting the variables in protected in BinaryExpression
	Expression* exp1;
private:
};

/*
All of the leaf nodes (child classes) are concrete classes and will override
all of the inherited methods. These methods will be implemented into the 
Expression.cpp file
*/

class Number : public Expression {
public:
	Number() = delete;
	Number(int n);
	virtual ~Number() override;  	

	int evaluate() const override;
	std::string type() const override;
	std::string print() const override;
protected:
private:
	int number;
};


class Multiply : public BinaryExpression {
public:
	Multiply() = delete;
	Multiply(Expression* subexp1,Expression* subexp2);
	virtual ~Multiply() override;  	

	int evaluate() const override;
	std::string type() const override;
	std::string print() const override;
protected:
private:
};


class Add : public BinaryExpression{
public:
	Add() = delete;
	Add(Expression* subexp1,Expression* subexp2);
	virtual ~Add() override;  	

	int evaluate() const override;
	std::string type() const override;
	std::string print() const override;
protected:
private:
};


class Abs : public UnaryExpression {
public:
	Abs() = delete;
	Abs(Expression* subexp);
	virtual ~Abs() override;  	

	int evaluate() const override;
	std::string type() const override;
	std::string print() const override;
protected:
private:
};

class Square : public UnaryExpression {
public:
	Square() = delete;
	Square(Expression* subexp);
	virtual ~Square() override;  	

	int evaluate() const override;
	std::string type() const override;
	std::string print() const override;
protected:
private:
};

#endif /* EXPRESSION_H_ */
