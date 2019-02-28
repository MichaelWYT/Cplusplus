#include <iostream>

#include "Point.h"
#include "Line.h"
#include "PLContainer.h"

using std::ostream;

// Initialise empty constructor
PLContainer::PLContainer() : lineCapacity(0), ptrCapacity(0),
                             lineLength(0), ptrLength(0)
{
  ptrArray = new Point[ptrCapacity];
  lineArray = new Line[lineCapacity];
}

// Deep Copy Constructor
PLContainer::PLContainer(const PLContainer &other) : lineCapacity(other.lineCapacity),
                                                     lineLength(other.lineLength), ptrCapacity(other.ptrCapacity), ptrLength(other.ptrLength)
{
  if (this != &other)
  {

    // Given a new object in memory, with same capacitity as other.
    lineArray = new Line[lineCapacity];

    // Copying all of the member variables.
    for (int i = 0; i < lineLength; i++)
    {
      lineArray[i] = other.lineArray[i];
    }

    // Repeat with ptrArray
    ptrArray = new Point[ptrCapacity];

    for (int i = 0; i < ptrLength; i++)
    {
      ptrArray[i] = other.ptrArray[i];
    }
  }
}

// Move constructor; Moving all values to our lvalue and then setting the expression value...
// to 0.
PLContainer::PLContainer(PLContainer &&other) : lineCapacity(other.lineCapacity),
                                                lineLength(other.lineLength), ptrCapacity(other.ptrCapacity), ptrLength(other.ptrLength),
                                                ptrArray(other.ptrArray), lineArray(other.lineArray)
{
  other.ptrCapacity = 0;
  other.ptrLength = 0;
  other.lineLength = 0;
  other.lineCapacity = 0;

  other.ptrArray = nullptr;
  other.lineArray = nullptr;
}

// Copy op=
PLContainer &PLContainer::operator=(const PLContainer &other)
{

  // As long as it's not the same array.
  if (this != &other)
  {

    // Delete the existing array set, if any.
    delete[] ptrArray;
    delete[] lineArray;

    // Construct a deep copy of the new PLContainer.
    PLContainer(other);
  }
  return *this;
}

// Move op=
PLContainer &PLContainer::operator=(PLContainer &&other)
{

  if (this != &other)
  {
    Point *tmpPtrArr = ptrArray;
    ptrArray = other.ptrArray;
    other.ptrArray = tmpPtrArr;

    Line *tmpLineArr = lineArray;
    lineArray = other.lineArray;
    other.lineArray = tmpLineArr;

    uint tmpLCap = lineCapacity;
    lineCapacity = other.lineCapacity;
    other.lineCapacity = tmpLCap;

    uint tmpLLen = lineLength;
    lineLength = other.lineLength;
    other.lineLength = tmpLLen;

    uint tmpPtrCap = ptrCapacity;
    ptrCapacity = other.ptrCapacity;
    other.ptrCapacity = tmpPtrCap;

    uint tmpPtrLen = ptrLength;
    ptrLength = other.ptrLength;
    other.ptrLength = tmpPtrLen;
  }
  return *this;
}

PLContainer::~PLContainer()
{
  if (ptrLength >= 0)
  {
    delete[] ptrArray;
  }

  if (lineLength >= 0)
  {
    delete[] lineArray;
  }
  ptrArray = nullptr;
  lineArray = nullptr;

  ptrLength = 0;
  lineLength = 0;
  ptrCapacity = 0;
  lineCapacity = 0;
}

bool PLContainer::operator==(const PLContainer &other) const
{
  bool check = false;
  // Checks if both containers are not empty, if they are return true.
  if (lineLength == 0 && ptrLength == 0 && other.numberOfPoints() == 0 && other.numberOfLines() == 0) {
    return true;
  } else {
    if (ptrLength == other.numberOfPoints() && lineLength == other.numberOfLines()) {
      // Check if this container has the same contents in other point array.
      for (int i = 0; i < ptrLength; i++) {
        check = false;
        for (int j = 0; j < other.numberOfPoints(); j++) {
          // If at any point the arrays are different return false.
          // op== should call the Point::op==
          // The point exists in the other array if true.
          if (ptrArray[i] == other.ptrArray[j]) {
            check = true;
          }
        }

        // Returns false if the point is not the same throughout other array.
        if (!check) {
          return false;
        }
      }

      // Check if this container has the same contents in the other line array.
      for (int i = 0; i < lineLength; i++) {
        check = false;
        for (int j = 0; j < other.numberOfLines(); j++){
          if (lineArray[i] == other.lineArray[j]) {
            check = true;
          }
        }

        if (!check) {
          return false;
        }
      }
    } else {
      return false;
    }
  }
    // No problems that means that they have the same contents.
    return true;
}

bool PLContainer::addPoint(double x, double y, Point *&point)
{

  // The getPoint() function sets the reference pointer if false
  if (getPoint(x, y, point)) {
    return false;
  } else {
    // We check if we need to resize
    if (ptrLength >= ptrCapacity) {
      resizePointsArray_(ptrCapacity + 1);
      ptrLength++;
    }

    // Then add the new pointer to the end and return true.
    Point newPoint(x, y);
    ptrArray[ptrLength - 1] = newPoint;
    point = &ptrArray[ptrLength - 1];
    return true;
  }
}

// If the point given exists then update the referenced pointer to
// the Point in the array. Else, we return false.
bool PLContainer::getPoint(double x, double y, Point *&point)
{

  Point tmpP(x, y);
  // Search through the entire array until you found the point.
  for (int i = 0; i < ptrLength; i++)
  {

    // Check if point (x,y) is in the container
    if (tmpP == ptrArray[i])
    {

      // Sets the reference pointer to the array element and returns true.
      point = &ptrArray[i];
      return true;
    }
  }

  // Entire Array searched does not contain the given point.
  return false;
}

// If the given point does not exist then we return false.
// Otherwise, we delete the point and all the lines defined by the point.
bool PLContainer::deletePoint(double x, double y)
{
  Point *tmpP;
  Point *tempArr;
  Line *lineP;

  uint c(0);
  // If it doesn't exist return false;
  if (!getPoint(x, y, tmpP))
  {
    return false;
  }
  else
  {
    getPoint(x, y, tmpP);
    tempArr = new Point[ptrCapacity];
    for (int i = 0; i < ptrLength; i++)
    {
      if (!(ptrArray[i] == *tmpP))
      {
        tempArr[c] = ptrArray[i];
        c++;
      }
    }

    // As tmpP is pointing to the array index in ptrArray from getPoint()
    // We can delete the point as long as it's in the lineArray.
    int p(0);
    while(getLine(x,y,ptrArray[p].getX(),ptrArray[p].getY(),lineP) && p < lineLength){
      deleteLine(x,y,ptrArray[p].getX(),ptrArray[p].getY());
      p++;
    }
    // Length is the number of points deleted (c);
    ptrLength = c;

    // Delete the array ptrArray was pointing to.
    delete[] ptrArray;

    // Points to a array with the points without the point we are deleting.
    ptrArray = tempArr;
    return true;
  }
}

unsigned int PLContainer::numberOfPoints() const
{
  return ptrLength;
}

// Checks if line((x1,y1)(x2,y2)) exist in the array
bool PLContainer::addLine(double x1, double y1, double x2, double y2, Line *&line)
{

  Point* tempP1 = new Point(x1,y1);
  Point* tempP2 = new Point(x2,y2);

  // If one of the points don't exist then return false.
  // Otherwise, we know the points exist.
  if (getPoint(x1, y1, tempP1) && (getPoint(x2, y2, tempP2))) {

    // If the line already exists then ref'ed pointer is updated
    // and returns false. Otherwise the line is not there.
    if (getLine(x1, y1, x2, y2, line)) {
      return false;
    } else {
      // Check for resize
      if (lineCapacity <= lineLength) {
        resizeLinesArray_(lineCapacity + 1);
        lineLength++;
      }

      Line tempL(tempP1, tempP2);

      // Add the new line to the end of lineArray
      lineArray[lineLength - 1] = tempL;
      line = &lineArray[lineLength - 1];
      return true;
    }
  }

  // An empty point (Doesn't exist) return false.
  return false;
}

// Gets the line in lineArray. If there is a line, update the referenced pointer
// and return true, else false.
bool PLContainer::getLine(double x1, double y1, double x2, double y2, Line *&line)
{

  Point *tempP1 = new Point(x1, y1);
  Point *tempP2 = new Point(x2, y2);
  Line *tempL = new Line(tempP1, tempP2);

  // Loop through lineArray, and return false if no line was found.
  for (int i = 0; i < lineLength; i++) {
    if (lineArray[i] == *tempL) {

      // Otherwise, update ref'ed pointer and return true.
      line = &lineArray[i];
      return true;
    }
  }

  // No line found.
  return false;
}

bool PLContainer::deleteLine(double x1, double y1, double x2, double y2)
{
  Line *linePtr;
  uint c(0);

  // Find if the line exists
  if (getLine(x1, y1, x2, y2, linePtr)) {
    //std::cout<<*linePtr<<"\n";
    Line* tempArray = new Line[lineCapacity];

    // If found we then loop through and copy the array into a temp
    // array. Then assign the temp array to lineArray.
    for (int i = 0; i < lineLength; i++)
    {
      if (!(lineArray[i] == *linePtr))
      {
        //std::cout<<lineArray[i]<<"\n";
        tempArray[c] = lineArray[i];
        c++;
      }
    }

    // New length for the array.
    lineLength = c;
    delete[] lineArray;
    lineArray = tempArray;
    for(int i(0);i<lineLength;i++){
    std::cout<<lineArray[i]<<"\n";
    }
    return true;
  }
  return false;
}

unsigned int PLContainer::numberOfLines() const
{
  return lineLength;
}

Line **PLContainer::incidentLines(double x, double y, unsigned int &number_lines, unsigned int &capacity)
{
  // IMPLEMENT ME
  Line **removeMe = nullptr;
  return removeMe;
}

void PLContainer::print(std::ostream &stream) const
{
  stream << "Points: ";
  for (int i = 0; i < ptrLength; i++)
  {
    stream << ptrArray[i];
    if (i + 1 != ptrLength)
    {
      stream << ", ";
    }
    else
    {
      stream << "\n";
    }
  }

  stream << "Lines: ";
  for (int j = 0; j < lineLength; j++)
  {
    stream << lineArray[j];
    if (j + 1 != lineLength)
    {
      stream << ", ";
    }
    else
    {
      stream << "\n";
    }
  }
}

std::ostream &operator<<(std::ostream &stream, const PLContainer &plc)
{
  stream << "Points: ";
  for (int i = 0; i < plc.numberOfPoints(); i++)
  {
    stream << plc.ptrArray[i];
    if (i + 1 != plc.numberOfPoints())
    {
      stream << ", ";
    }
    else
    {
      stream << "\n";
    }
  }

  stream << "Lines: ";
  for (int j = 0; j < plc.numberOfLines(); j++)
  {
    stream << plc.lineArray[j];
    if (j + 1 != plc.numberOfLines())
    {
      stream << ", ";
    }
    else
    {
      stream << "\n";
    }
  }
  return stream;
}

void PLContainer::resizePointsArray_(unsigned int new_capacity)
{
  if (new_capacity > ptrCapacity)
  {
    // Creates a temporary pointer to the new array in dynamic memory.
    Point *temp = new Point[new_capacity];
    for (uint i = 0; i < ptrLength; i++)
    {
      temp[i] = ptrArray[i];
    }

    // After setting capacity to the new capacity, delete the old array
    // from dynamic memory and point to the new one.
    ptrCapacity = new_capacity;
    delete[] ptrArray;
    ptrArray = temp;
  }
}

void PLContainer::resizeLinesArray_(unsigned int new_capacity)
{
  if (new_capacity > lineCapacity)
  {
    // Creates a temporary pointer to the new array in dynamic memory.
    Line *temp = new Line[new_capacity];
    for (uint i = 0; i < lineLength; i++)
    {
      temp[i] = lineArray[i];
    }

    // After setting capacity to the new capacity, delete the old array
    // from dynamic memory and point to the new one.
    lineCapacity = new_capacity;
    delete[] lineArray;
    lineArray = temp;
  }
}
