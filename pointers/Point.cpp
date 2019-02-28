#include <iostream>
#include <cmath>
#include <cfloat>

#include "Point.h"

using std::ostream;

Point::Point() : xCoord(0.0), yCoord(0.0) {
}

Point::Point(double x, double y) : xCoord(x), yCoord(y) {
}

// Copy Constructor to copy all member variables
Point::Point(const Point& other) {
	this->xCoord = other.xCoord;
	this->yCoord = other.yCoord;
}

// Move Constructor
Point::Point(Point&& other) : xCoord(other.xCoord), yCoord(other.yCoord){
	other.xCoord = 0.0;
	other.yCoord = 0.0;
}

// Assigning lvalue
Point& Point::operator=(const Point& other) {
	if(this != &other){
		this->xCoord = other.xCoord;
		this->yCoord = other.yCoord;
	}
	return *this;
}

Point& Point::operator=(Point&& other){
	if(this != &other){
		double tempX = xCoord;
		xCoord = other.getX();
		other.xCoord = tempX;

		double tempY = yCoord;
		yCoord = other.getY();
		other.yCoord = tempY;
	}

	return *this;
}

Point::~Point() {
	xCoord = 0.0;
	yCoord = 0.0;
}

double Point::getX()const{
	//std::cout<<xCoord<<" \n";
	return this->xCoord;
}

double Point::getY()const{
	//std::cout<<yCoord<<" \n";
	return this->yCoord;
}

// Returns true when both points(x,y) are equal
bool Point::operator==(const Point& other) const{
	if(approxEqual(this->xCoord,other.xCoord) && approxEqual(this->yCoord,other.yCoord)){
		return true;
	} else {
		return false;
	}
}

void Point::print(std::ostream& stream) const{
	stream<<"("<<xCoord<<", "<<yCoord<<")";
}

ostream& operator<<(std::ostream& stream, const Point& point){
	stream<<"("<<point.getX()<<", "<<point.getY()<<")";
	return stream;
}

bool approxEqual(double a,double b){

	const double PRECISION=1000000;

	if(a==b)
		return true;

	double difference = fabs(a - b);
	if (difference <= DBL_EPSILON)
		return true;

	a = fabs(a);
	b = fabs(b);
	double scaledEpsilon = DBL_EPSILON * PRECISION;
	scaledEpsilon = a > b ? a * scaledEpsilon  : b * scaledEpsilon;

	return difference <= scaledEpsilon;

}
