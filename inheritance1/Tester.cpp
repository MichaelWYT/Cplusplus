#include <stdlib.h>
#include <iostream>
#include <utility>
#include <sstream> 

#include "Tester.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;

Tester::Tester() : error_(false), funcname_("") {
	unsigned int val(time(0)*rand());
	srand(val);
}

Tester::~Tester() {
}

void Tester::testCtorNumber(){
    funcname_ = "testCtorNumber";

    int n = generateInt_();
    Number* ne = new Number(n);
    if (ne->evaluate() != n) {
        errorOut_("Construction of Number.",1);
    }
    delete ne;

    passOut_("Tested the constructor of class Number.");
}

void Tester::testCtorMultiply(){
    funcname_ = "testCtorMultiply";

    int n1 = generateInt_();
    int n2 = generateInt_();
    Number* ne1 = new Number(n1);
    Number* ne2 = new Number(n2);
    
    Multiply* me = new Multiply(ne1,ne2);
    if (me->evaluate() != n1*n2) {
        errorOut_("Construction of Multiply.",1);
    }

    delete me;

    passOut_("Tested the constructor of class Multiply.");

}

void Tester::testCtorAdd(){
    funcname_ = "testCtorAdd";

    int n1 = generateInt_();
    int n2 = generateInt_();
    Number* ne1 = new Number(n1);
    Number* ne2 = new Number(n2);
    
    Add* ae = new Add(ne1,ne2);
    if (ae->evaluate() != n1+n2) {
        errorOut_("Construction of Add.",1);
    }

    delete ae;

    passOut_("Tested the constructor of class Add.");

}

void Tester::testCtorAbs(){
    funcname_ = "testCtorAbs";
    
    int pos = rand()+1;
    int neg = (-1) * (rand()+1);
    
    Number* pose = new Number(pos);
    Number* nege = new Number(neg);
    Number* zeroe  = new Number(0);

    Abs* a_pos = new Abs(pose);
    Abs* a_neg = new Abs(nege);
    Abs* a_zero = new Abs(zeroe);

    if (a_pos->evaluate() != pos) {
        errorOut_("Construction of Abs with positive value.",1);
    }
    if (a_neg->evaluate() != -1*neg) {
        errorOut_("Construction of Abs with negative value.",2);
    }
    if (a_zero->evaluate() != 0) {
        errorOut_("Construction of Abs with value 0.",3);
    }
    
    delete a_pos;
    delete a_neg;
    delete a_zero;

    passOut_("Tested the constructor of class Abs.");

}

void Tester::testCtorSquare(){
    funcname_ = "testCtorSquare";

    int pos = rand()+1;
    int neg = (-1) * (rand()+1);
    
    Number* pose = new Number(pos);
    Number* nege = new Number(neg);
    Number* zeroe  = new Number(0);

    Square* s_pos = new Square(pose);
    Square* s_neg = new Square(nege);
    Square* s_zero = new Square(zeroe);

    if (s_pos->evaluate() != pos*pos) {
        errorOut_("Construction of Square with positive expression.",1);
    }
    if (s_neg->evaluate() != neg*neg) {
        errorOut_("Construction of Square with negative expression.",2);
    }
    if (s_zero->evaluate() != 0) {
        errorOut_("Construction of Square with expression 0.",3);
    }
    
    delete s_pos;
    delete s_neg;
    delete s_zero;

    passOut_("Tested the constructor of class Square.");

}

void Tester::testTypeNumber(){
    funcname_ = "testTypeNumber";

    int n = generateInt_();
    Number* ne = new Number(n);
    if (ne->type() != "Number") {
        errorOut_("Wrong type of Number object.",1);
    }

    Expression* e = ne;
    if (e->type() != "Number") {
        errorOut_("Wrong type of Number object.",2);
    }    

    delete ne;

    passOut_("Tested function type of class Number.");

}

void Tester::testTypeMultiply(){    
    funcname_ = "testTypeMultiply";

    int n1 = generateInt_();
    int n2 = generateInt_();
    Number* ne1 = new Number(n1);
    Number* ne2 = new Number(n2);
    
    Multiply* me = new Multiply(ne1,ne2);
    if (me->type() != "Multiply") {
        errorOut_("Wrong type of Multiply object.",1);
    }

    Expression* e = me;
    if (e->type() != "Multiply") {
        errorOut_("Wrong type of Multiply object.",2);
    }

    delete me;

    passOut_("Tested function type of class Multiply.");
}

void Tester::testTypeAdd(){   
    funcname_ = "testTypeAdd";

    int n1 = generateInt_();
    int n2 = generateInt_();
    Number* ne1 = new Number(n1);
    Number* ne2 = new Number(n2);
    
    Add* ae = new Add(ne1,ne2);
    if (ae->type() != "Add") {
        errorOut_("Wrong type of Add object.",1);
    }

    Expression* e = ae;
    if (e->type() != "Add") {
        errorOut_("Wrong type of Add object.",2);
    }

    delete ae;

    passOut_("Tested function type of class Add.");
}

void Tester::testTypeAbs(){    
    funcname_ = "testTypeAbs";

    int n = generateInt_();

    Number* ne = new Number(n);

    Abs* ae = new Abs(ne);

    if (ae->type() != "Abs") {
        errorOut_("Wrong type of Abs object.",1);
    }
    Expression* e = ae;
    if (e->type() != "Abs") {
        errorOut_("Wrong type of Abs object.",2);
    }
    delete ae;

    passOut_("Tested function type of class Abs.");
}

void Tester::testTypeSquare(){    
    funcname_ = "testTypeSquare";

    int n = generateInt_();

    Number* ne = new Number(n);

    Square* se = new Square(ne);

    if (se->type() != "Square") {
        errorOut_("Wrong type of Square object.",1);
    }
    Expression* e = se;
    if (e->type() != "Square") {
        errorOut_("Wrong type of Square object.",2);
    } 
    delete se;


    passOut_("Tested function type of class Square.");
}

void Tester::testPrintNumber(){    
    funcname_ = "testPrintNumber";

    int n=generateInt_();

    Number* ne=new Number(n);
    string str=std::to_string(n);
    if (ne->print() != str) {
        errorOut_("Wrong string for Number object.",1);
    }
    Expression* e = ne;
    if (e->print() != str) {
        errorOut_("Wrong string for Number object.",2);
    }

    delete ne;

    passOut_("Tested function print of class Number.");
}

void Tester::testPrintMultiply(){    
    funcname_ = "testPrintMultiply";

    int n1 = generateInt_();
    int n2 = generateInt_();
    Number* ne1 = new Number(n1);
    Number* ne2 = new Number(n2);
    
    string str = std::string("(") + std::to_string(n1) + "*" + std::to_string(n2) + ")";

    Multiply* me = new Multiply(ne1,ne2);
    if (me->print() != str) {
        errorOut_("Wrong string for Multiply object.",1);
    }

    Expression* e = me;
    if (e->print() != str) {
        errorOut_("Wrong string for Multiply object.",2);
    }

    delete me;

    passOut_("Tested function print of class Multiply.");
}

void Tester::testPrintAdd(){    
    funcname_ = "testPrintAdd";

    int n1 = generateInt_();
    int n2 = generateInt_();
    Number* ne1 = new Number(n1);
    Number* ne2 = new Number(n2);
    
    string str = std::string("(") + std::to_string(n1) + "+" + std::to_string(n2) + ")";

    Add* ae = new Add(ne1,ne2);
    if (ae->print() != str) {
        errorOut_("Wrong string for Add object.",1);
    }

    Expression* e = ae;
    if (e->print() != str) {
        errorOut_("Wrong string for Add object.",2);
    }

    delete ae;
    passOut_("Tested function print of class Add.");
}

void Tester::testPrintAbs(){    
    funcname_ = "testPrintAbs";

    int n = generateInt_();
    Number* ne = new Number(n);

    string str = std::string("Abs(") + std::to_string(n)+ ")";

    Abs* ae = new Abs(ne);
    if (ae->print() != str) {
        errorOut_("Wrong string for Abs object.",1);
    }

    Expression* e = ae;
    if (e->print() != str) {
        errorOut_("Wrong string for Abs object.",2);
    }

    delete ae;

    passOut_("Tested function print of class Abs.");
}

void Tester::testPrintSquare(){    
    funcname_ = "testPrintSquare";

    int n = generateInt_();
    Number* ne = new Number(n);

    string str = std::string("Square(") + std::to_string(n)+ ")";

    Square* se = new Square(ne);
    if (se->print() != str) {
        errorOut_("Wrong string for Square object.",1);
    }

    Expression* e = se;
    if (e->print() != str) {
        errorOut_("Wrong string for Square object.",2);
    }

    delete se;
    
    passOut_("Tested function print of class Square.");
}

void Tester::testPrintRandom(){    
    funcname_ = "testPrintRandom";

    bool fail=false;
    for(int i =0; i < NUM_EXPRESSIONS;++i){
        int val=0;
        string str="";
        Expression* e=generateExpression_(val,str,EXPRESSION_DEPTH);
        if (!fail && e->print() != str) {
            errorOut_("Wrong string for random expression.",1);
            fail=true;
         }
        delete e;

    }

    passOut_("Tested function print for random expressions.");
}

void Tester::testEvaluateNumber(){    
    funcname_ = "testEvaluateNumber";

    int n=generateInt_();

    Number* ne=new Number(n);
   
    if (ne->evaluate() != n) {
        errorOut_("Wrong value for Number object.",1);
    }
    Expression* e = ne;
    if (e->evaluate() != n) {
        errorOut_("Wrong value for Number object.",2);
    }

    delete ne;

    passOut_("Tested function evaluate of class Number.");
}

void Tester::testEvaluateMultiply(){    
    funcname_ = "testEvaluateMultiply";

    int n1 = generateInt_();
    int n2 = generateInt_();
    Number* ne1 = new Number(n1);
    Number* ne2 = new Number(n2);
    
    int val = n1*n2;

    Multiply* me = new Multiply(ne1,ne2);

    if (me->evaluate() != val) {
        errorOut_("Wrong value for Multiply object.",1);
    }

    Expression* e = me;
    if (e->evaluate() != val) {
        errorOut_("Wrong value for Multiply object.",2);
    }

    delete me;

    passOut_("Tested function evaluate of class Multiply.");
}

void Tester::testEvaluateAdd(){    
    funcname_ = "testEvaluateAdd";

    int n1 = generateInt_();
    int n2 = generateInt_();
    Number* ne1 = new Number(n1);
    Number* ne2 = new Number(n2);
    
    int val = n1+n2;

    Add* ae = new Add(ne1,ne2);
    if (ae->evaluate() != val) {
        errorOut_("Wrong value for Add object.",1);
    }

    Expression* e = ae;
    if (e->evaluate() != val) {
        errorOut_("Wrong value for Add object.",2);
    }

    delete ae;

    passOut_("Tested function evaluate of class Add.");
}

void Tester::testEvaluateAbs(){    
    funcname_ = "testEvaluateAbs";

    int n = generateInt_();
    Number* ne = new Number(n);

    int val = abs(n);

    Abs* ae = new Abs(ne);
    if (ae->evaluate() != val) {
        errorOut_("Wrong value for Abs object.",1);
    }

    Expression* e = ae;
    if (e->evaluate() != val) {
        errorOut_("Wrong value for Abs object.",2);
    }

    delete ae;

    passOut_("Tested function evaluate of class Abs.");
}

void Tester::testEvaluateSquare(){    
    funcname_ = "testEvaluateSquare";

    int n = generateInt_();
    Number* ne = new Number(n);

    int val = n*n;

    Square* se = new Square(ne);
    if (se->evaluate() != val) {
        errorOut_("Wrong value for Square object.",1);
    }

    Expression* e = se;
    if (e->evaluate() != val) {
        errorOut_("Wrong value for Square object.",2);
    }

    delete se;

    passOut_("Tested function evaluate of class Square.");
}

void Tester::testEvaluateRandom(){    
    funcname_ = "testEvaluateRandom";

    bool fail=false;
    for(int i =0; i < NUM_EXPRESSIONS;++i){
        int val=0;
        string str="";
        Expression* e=generateExpression_(val,str,EXPRESSION_DEPTH);
        if (!fail && e->evaluate() != val) {
            errorOut_("Wrong value for random expression.",1);
            fail=true;
         }
        delete e;
    }

    passOut_("Tested function print for random expressions.");
}


Expression*  Tester::generateExpression_(int& value, std::string& str, unsigned int depth) {
    
    int val1,val2;
    std::string str1,str2;
    Expression *e1(nullptr),*e2(nullptr);
   
    unsigned int choice = (depth ? rand()%5 : 0);
    switch (choice) {
    case 4:
    {
        e1=generateExpression_(val1,str1,depth-1);
        e2=generateExpression_(val2,str2,depth-1);
        value = val1*val2;
        str = std::string("(") + str1 + "*" + str2 + ")";
        return new Multiply(e1,e2);
    }
    case 3:
    {
        e1=generateExpression_(val1,str1,depth-1);
        e2=generateExpression_(val2,str2,depth-1);
        value = val1+val2;
        str = std::string("(") + str1 + "+" + str2 + ")";
        return new Add(e1,e2);
    }
    case 2:
    {
        e1=generateExpression_(val1,str1,depth-1);
        value = (val1 < 0 ? (-1)*val1 : val1);
        str = std::string("Abs(") + str1 + ")";
        return new Abs(e1);
    }
    case 1:
        e1=generateExpression_(val1,str1,depth-1);
        value = val1*val1;
        str = std::string("Square(") + str1 + ")";
        return new Square(e1);
    case 0:
    default:
    {
        value = generateInt_();
        str = std::to_string(value);
        return new Number(value);
    }
    }
}

int Tester::generateInt_(){
    int sign = (rand()%2 ? -1 : 1);
    return (sign * rand());
}

void Tester::errorOut_(const string& errMsg, unsigned int errBit) {
        cerr << funcname_ << " " << "(fail";
        if (errBit)
                cerr << errBit;
        cerr << "): " << errMsg << endl;
        error_|=(1<<errBit);
}

void Tester::passOut_(const string& passMsg) {
        if (!error_) {
                cerr << funcname_ << " " << "(pass): " << passMsg << endl;
        }
}
