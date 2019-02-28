
#include <iostream>
#include <string>

#include "Tester.h"


using std::cout;
using std::endl;


int main(int argc, char* argv[]) {

	while (argc > 1) {
		switch (argv[--argc][0]) {
		case 'a':
		{
			Tester t;
			t.testCtorNumber();
		}
		break;
		case 'b':
		{
			Tester t;
			t.testCtorMultiply();
		}
		break;
		case 'c':
		{
			Tester t;
			t.testCtorAdd();
		}
		break;
		case 'd':
		{
			Tester t;
			t.testCtorAbs();
		}
		break;
		case 'e':
		{
			Tester t;
			t.testCtorSquare();
		}
		break;
		case 'f':
		{
			Tester t;
			t.testTypeNumber();
		}
		break;
		case 'g':
		{
			Tester t;
			t.testTypeMultiply();
		}
		break;
		case 'h':
		{
			Tester t;
			t.testTypeAdd();
		}
		break;
		case 'i':
		{
			Tester t;
			t.testTypeAbs();
		}
		break;
		case 'j':
		{
			Tester t;
			t.testTypeSquare();
		}
		break;
		case 'k':
		{
			Tester t;
			t.testPrintNumber();
		}
		break;
		case 'l':
		{
			Tester t;
			t.testPrintMultiply();
		}
		break;
		case 'm':
		{
			Tester t;
			t.testPrintAdd();
		}
		break;
		case 'n':
		{
			Tester t;
			t.testPrintAbs();
		}
		break;
		case 'o':
		{
			Tester t;
			t.testPrintSquare();
		}
		break;
		case 'p':
		{
			Tester t;
			t.testPrintRandom();
		}
		break;
		case 'q':
		{
			Tester t;
			t.testEvaluateNumber();
		}
		break;
		case 'r':
		{
			Tester t;
			t.testEvaluateMultiply();
		}
		break;
		case 's':
		{
			Tester t;
			t.testEvaluateAdd();
		}
		break;
		case 't':
		{
			Tester t;
			t.testEvaluateAbs();
		}
		break;
		case 'u':
		{
			Tester t;
			t.testEvaluateSquare();
		}
		break;
		case 'v':
		{
			Tester t;
			t.testEvaluateRandom();
		}
		break;
		default:
		{
			cout<<"Options are a -- v."<<endl;
		}
		break;
       	}
	}
	
	return 0;
}

