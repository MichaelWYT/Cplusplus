#ifndef LINE_H_
#define LINE_H_

#include<iostream>

#include "Point.h"

/*
* Objects of the class Line represent lines defined by two two-dimensional 
* points. The points are stored as pointers to objects of class Point.
* One important issue about Line is that it does not own the Point 
* objects to which it stores pointers. This means that the only way to 
* provide the points defining a line is by someone else allocating these
* points and giving them to the Line ready made. As the constructors and 
* other methods of Line do not allocate the memory for the Point objects,
* the methods of the class are not in charge of deallocating this memory.
* It would be an error to deallocate this memory even by the destructor.
* Similarly, the copy constructor of Line should not create new Point 
* objects, but instead perfom a shallow copy of the Point pointers.
* Your job is to complete the implementation by adding private variables
* and complete all the function members of the class given below.
*/

class Line {
 public:
  
  // Creates a line with both points null
  Line();

  // Creates a line defined by the two 
  // points given as parameters as pointers
  // to Point objects. If the Point objects
  // are equal, we have a degenerate line
  // that is a single point.
  Line(Point *p1, Point *p2);

  // Copy constructor 
  // Performs a shallow copy
  Line(const Line& other);
  
  // Move constructor
  Line(Line&& other);

 // Assignment operator (copy)
 // Performs a shallow copy
  Line& operator=(const Line& other);

  // Assignment operator (move)
  Line& operator=(Line&& other);
 
  // Destructor
  ~Line();

  // Returns true if the given point 
  // lies on the line and false otherwise 
  bool isIncident(const Point& point)const;

  // Compares two lines for equivalence.
  // Returns true if both lines have both of their
  // points set to non-null values, and 
  // the two pairs of points define the same line 
  // (that is, either both lines are single points
  // that are equal, or both are "proper" lines
  // and all points from the two pairs are on the
  // same line). Returns false otherwise.
  bool operator==(const Line& other) const;

  // Returns the first Point pointer 
  const Point* getPoint1()const;

  // Returns the second Point pointer 
  const Point* getPoint2()const;

  // Prints the coordinates of the two points
  // defining the line, or nothing if some of them
  // is not set (i.e., if some is a null pointer)
  void print(std::ostream& stream) const;
  
  // Prints the coordinates of the two points
  // defining the line or nothing if some of them
  // is not set (i.e., if some is a null pointer)
  friend std::ostream& operator<<(std::ostream& stream,const Line& line);



 private:
	Point* point1; 
    Point* point2;
};

#endif /* LINE_H_ */