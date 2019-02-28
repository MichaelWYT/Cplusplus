#include <iostream>

#include "Line.h"

using std::ostream;

Line::Line() : point1(nullptr), point2(nullptr) {
}

Line::Line(Point* p1, Point* p2) : point1(nullptr), point2(nullptr) {
	point1 = p1;
	point2 = p2;
}

// Shallow Copy Constructor
Line::Line(const Line& other) : point1(other.point1), point2(other.point2) {
	*this = other;
}

Line::Line(Line&& other) : point1(other.point1), point2(other.point2) {
	other.point1 = nullptr;
	other.point2 = nullptr;
}

// Copy Operator
Line& Line::operator=(const Line& other) {
	if(this != &other){
		point1 = other.point1;
		point2 = other.point2;
	}
	return *this;
}

// Move Operator
Line& Line::operator=(Line&& other) {
	if(this != &other){
		this->point1 = other.point1;
		this->point2 = other.point2;
		other.point1 = nullptr;
		other.point2 = nullptr;
	}
	return *this;
}

// Deconstructor
Line::~Line() {
	point1 = nullptr;
	point2 = nullptr;
}

// Checks if the given point lies on the line ONLY
bool Line::isIncident(const Point& point)const {
	// Given line: (y-y1)(x2-x1)=(x-x1)(y2-1)
	double y1=point1->getY(), y2=point2->getY();
	double x1=point1->getX(), x2=point2->getX();

	// We use approxEqual from point.cpp to compare the double values
	if(approxEqual((point.getY()-y1)*(x2-x1), (point.getX()-x1)*(y2-y1))){
		return true;
	}
	return false;
}

// Checks if 2 points are equal by checking if they define the same line
// or they are both lines and overlap each other.
// OR both points are the same.
bool Line::operator==(const Line& other)const {
	if ((isIncident(*other.getPoint1()) && isIncident(*other.getPoint2())) 
			|| (other.getPoint1()==point1 && other.getPoint2()==point2)) {
		return true;
	}
	else {
		return false;
	}
}

const Point* Line::getPoint1()const {
	return point1;
}

const Point* Line::getPoint2()const {
	return point2;
}

void Line::print(std::ostream& stream) const {
	stream << "(" << *getPoint1() << ", " << *getPoint2() << ")";
}

ostream& operator<<(std::ostream& stream, const Line& line) {
	stream << "(" << *line.getPoint1() << ", " << *line.getPoint2() << ")";
	return stream;
}
