#ifndef POINT_H_
#define POINT_H_

/*
* Objects of the class Point represent two-dimensional points in real
* coordinate space. That is, pairs (x,y) where x and y are real numbers.
* Here, coordinates are modelled by data members of type double.
* Since floating point arithmetic is not exact, instead of comparing 
* double values with == or !=, in this assignment you will use the function 
* approxEqual, which has been implemented for you.
* Your job is to complete the implementation by adding private variables
* and complete all the function members of the class given below.
*/

#include<iostream>

class Point {
 public:
  
  // Create a point (0,0)
  Point();

  // Create a point with coordinates (x, y)
  Point(double x, double y);

  // Copy constructor
  Point(const Point& other);
  
  // Move constructor
  Point(Point&& other);

  // Assignment operator (copy)
  Point& operator=(const Point& other);

  // Assignment operator (move)
  Point& operator=(Point&& other);
 
  // Destructor
  ~Point();

  // Returns the x-coordinate 
  double getX()const;

  // Returns the y-coordinate 
  double getY()const;

  // Returns true if the two points are equal.
  // Returns false otherwise.
  bool operator==(const Point& other) const;
 
  // Prints the coordinates of the point
  void print(std::ostream& stream) const;

  // Prints the coordinates of the point
  friend std::ostream& operator<<(std::ostream& stream, const Point& point);

 private:

  double xCoord,yCoord;
};

// Compares two double values for equality
// up to a certain precision. Returns true
// if a and b are approximately equal, 
// and returns false otherwise.
bool approxEqual(double a, double b);

#endif /* POINT_H_ */
