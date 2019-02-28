#ifndef TESTER_H_
#define TESTER_H_

#include <string>
#include <vector>
#include "Expression.h"

using std::string;
using std::vector;

class Tester {
	
public:
	Tester();
	~Tester();

	void testCtorNumber();
	void testCtorMultiply();
	void testCtorAdd();
	void testCtorAbs();
	void testCtorSquare();

	void testTypeNumber();
	void testTypeMultiply();
	void testTypeAdd();
	void testTypeAbs();
	void testTypeSquare();

	void testPrintNumber();
	void testPrintMultiply();
	void testPrintAdd();
	void testPrintAbs();
	void testPrintSquare();
	void testPrintRandom();

	void testEvaluateNumber();
	void testEvaluateMultiply();
	void testEvaluateAdd();
	void testEvaluateAbs();
	void testEvaluateSquare();
	void testEvaluateRandom();
	
private:

	int generateInt_();
	Expression*  generateExpression_(int& value, std::string& str, unsigned int depth);
	
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	void passOut_(const std::string& passMsg);

	char error_;
	std::string funcname_;

	const unsigned int NUM_EXPRESSIONS = 100;
	const unsigned int EXPRESSION_DEPTH = 5;
	
};

#endif /* TESTER_H_ */
