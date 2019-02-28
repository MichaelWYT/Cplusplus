#ifndef PLCONTAINER_H_
#define PLCONTAINER_H_

#include<iostream>

#include "Point.h"
#include "Line.h"

/*
* PLContainer is a container for storing and managing points and lines.
* More precisely, it stores two arrays, one of pointers to objects of
* class Point, and one of pointers to objects of class Line.
* It manages (allocates and frees) the memory for all the Point and Line
* objects and the arrays storing the pointers. 
* When adding points and lines, reserving additional space for the 
* corresponding array may be necessary. For this, the private member
* functions resizePointsArray_ and resizeLinesArray_ should be implemented.
* When an object of class PLContainer is destroyed, all the memory allocated 
* for it should be deallocated.
* Your job is to complete the implementation by adding private variables
* and complete all the function members of the class given below.
*/

class PLContainer {
 public:
  
  // Creates an empty container with no space reserved
  PLContainer();

  // Copy constructor
  // Performs a deep copy
  PLContainer(const PLContainer& other);
  
  // Move constructor
  PLContainer(PLContainer&& other);

  // Assignment operator (copy)
  // Performs a deep copy
  PLContainer& operator=(const PLContainer& other);

  // Assignment operator (move)
  PLContainer& operator=(PLContainer&& other);
 
  // Destructor
  ~PLContainer();

  // Returns true if two containers have 
  // (1) the same sets of points (the order in 
  // which points are stored does NOT matter) and
  // (2) the same sets of lines, where lines are
  // compared using the == operator in class Line  
  // that compares lines for equivalence (the order
  // in which lines are stored does NOT matter). 
  // Returns false if any of (1) or (2) is false.
  // Note: if both containers are empty, returns true.
  bool operator==(const PLContainer& other) const;

  // Tries to add the point (x, y) to the container.
  // If the point is already in the container,
  // updates the reference pointer to the pointer to
  // the existing Point and returns false.
  // Otherwise, allocates a new Point, adds the pointer
  // to the end of the corresponding array, sets the
  // reference pointer to this pointer and returns true.
  bool addPoint(double x, double y, Point*& point);

  // If a point with the given coordinates does not exist in the
  // container, returns false. Otherwise, updates the reference 
  // pointer to that Point and returns true.
  bool getPoint(double x, double y, Point*& point);

  // If a point with the given coordinates does not exist in the
  // container, returns false. Otherwise, deletes the point and 
  // deletes all the lines in the container that are defined 
  // using this point, and returns true.
  bool deletePoint(double x, double y);

  // Returns the number of points in the container.
  unsigned int numberOfPoints() const;

  // Tries to add a new line defined by the points (x1,y1) and (x2,y2).
  // If one of the points does not exist in the container, 
  // does nothing and returns false.
  // If the container already contains a line equivalent to the one 
  // defined by the two points, updates the reference pointer to 
  // the pointer for the existing Line and returns false. 
  // Otherwise, creates the new Line, adds it to the container 
  // at the end of the corresponding array, 
  // updates the reference pointer to the new Line and returns true.
  bool addLine(double x1, double y1, double x2, double y2, Line*& line);

  // If there is a line in the container equivalent to the line defined by 
  // the points (x1,y1) and (x2,y2), updates the pointer reference to this 
  // Line and returns true. If there is not such a line, returns false.
  bool getLine(double x1, double y1, double x2, double y2, Line*& line);

  // Deletes the line defined by the points (x1,y1) and (x2,y2). 
  // If this line does not exist, returns false, otherwise returns true.
  bool deleteLine(double x1, double y1, double x2, double y2);

  // Returns the number of lines in the container
  unsigned int numberOfLines() const;

  // Returns a dynamic memory array holding all the pointers to lines in the container
  // on which the given point (x,y) lies. The reference integer number_lines is updated 
  // to the number of such lines, and the reference integer capacity is set to 
  // to the capacity of the returned array.
  Line** incidentLines(double x, double y, unsigned int& number_lines, unsigned int& capacity);


  // Prints the points and lines in the container
  void print(std::ostream& stream) const;
  
  // Prints the points and lines in the container
  friend std::ostream& operator<<(std::ostream& stream, const PLContainer& plc);

 private:
  Point* ptrArray;
  Line* lineArray;
  uint lineCapacity;
  uint ptrCapacity;
  uint lineLength;
  uint ptrLength;

  // Resizes the space reserved for the array of Point* to new_capacity. 
  // Resizing has no effect on the contents.
  // If new_capacity is smaller or equal to the current capacity of the array,
  // does nothing.
  void resizePointsArray_(unsigned int new_capacity);

  // Resizes the space reserved for the array of Line* to new_capacity. 
  // Resizing has no effect on the contents.
  // If new_capacity is smaller or equal to the current capacity of the array,
  // does nothing. and returns true. 
  void resizeLinesArray_(unsigned int new_capacity);

};

#endif /* PLCONTAINER_H_ */