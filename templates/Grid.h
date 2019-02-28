#ifndef GRID_H_
#define GRID_H_

#include <iosfwd>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include <stack>
#include <list>
#include <set>

/* 

In this exercise you will implement a class representing
 a terrain in the form of a rectangular grid. The cells of the
 grid are indexed with pairs of integers, where (0,0) 
 represents the lower left cell, and (m-1,n-1) represents
 the top right cell, where m is the width and n is the height 
 of the grid. For example, a grid of width 4 and height 3 is 
 indexed in the following way:

(0,2)(1,2)(2,2)(3,2)
(0,1)(1,1)(2,1)(3,1)
(0,0)(1,0)(2,0)(3,0)

Some of the cells of the grid are blocked by obstacles.
We are interested in determining whether there is a path to 
reach a given goal cell from a given start cell by moving 
one cell at a time in each of the four cardinal directions: 
North, East, West, South, and never entering a blocked cell
or stepping outside of the grid. You will write functions 
that compute and output such a path if it exists.

In the example above, suppose that cells (3,0), (3,2),
(0,1) and (1,1) are blocked. If the start is (0,0) and
the goal is (0,2), then we have the following path 
(0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2).

You are advised to use the STL containers for storing
information. This should help you implement this class.

*/

class Grid {
public:
	// Default constructor. Initializes an empty grid, 
	// with both dimensions equal to 0.
	Grid();

	// Destructor
	~Grid();

	// No need to implement copy and move constructors
	Grid(const Grid&) = delete;
	Grid(Grid&&) = delete;
	// No need to implement assignment operators
	Grid& operator=(const Grid& other) = delete;
	Grid& operator=(Grid&& other) = delete;



	/* 

	Loads a grid description from a file. 
	The format of the file is as follows: 
	 -- the first line is 
	 START(X1,Y1)
	 where X1 and Y1 are integer numbers.
	 -- the second line is 
	 GOAL(X2,Y2)
	 where X2 and Y2 are integer numbers.
	 -- the remaining lines show the grid as follows

	ooox
	xxoo
    ooox

	where o represents an empty cell, and x represents a blocked
	cell. The lower left symbol is cell (0,0), and the top right 
	symbol is cell (m-1,n-1), where m is the width and n is the height 
	of the grid (in the above example, m=4, n=3). In the file there 
	is no empty line between GOAL(X2,Y2) and the grid.
	If the file does not exist or there is an error during reading, 
	throw "Error loading grid description."
	If the start or end position is outside of the grid, throw 
	"Position outside of the range of the grid."
	 */
	void loadFromFile(const std::string& filename);

	// Returns true if (x,y) is the start position, and 
	// returns false otherwise. 
	// If (x,y) is outside of the grid, throw 
	// "Position outside of the range of the grid."
	bool isStart(int x,int y) const;

	// Returns true if (x,y) is the goal position, and 
	// returns false otherwise. 
	// If (x,y) is outside of the grid, throw 
	// "Position outside of the range of the grid."
	bool isGoal(int x,int y) const;

	// Returns true if (x,y) is a blocked cell, and 
	// returns false otherwise. 
	// If (x,y) is outside of the grid, throw
	// "Position outside of the range of the grid."
	bool blocked(int x, int y) const;

	// Sets (x,y) to be the start position.
	// If  (x,y) is outside of the grid,
	// throw "Position outside of the range of the grid."
	void setStart(int x, int y);

	// Sets (x,y) to be the goal position.
	// If (x,y) is outside of the grid,
	// throw "Position outside of the range of the grid."
	void setGoal(int x, int y);

	// Sets cell (x,y) to empty (can be entered).
	// If (x,y) is outside of the grid,
	// throw "Position outside of the range of the grid."
	void unblock(int x, int y);

	// Sets cell (x,y) to blocked (cannot be entered).
	// If (x,y) is outside of the grid,
	// throw "Position outside of the range of the grid."
	void block(int x, int y);

	// Returns true if there is a path from the current 
	// start to the current end position, and false otherwise.
	// A path cannot pass through blocked cells or exit the 
	// grid, and from a given cell can move in one step in each
	// of the four neighboring cells, in the cardinal directions: 
	// North, East, West, South 
	bool existsPath();


	/* 
	Outputs the path from the start to the goal position as 
	follows:

	g**x
	xx*o
    s**x

	where s denotes the start position (here (0,0)), 
	g denotes the end position, and the * symbols denote the cells
	visited in this path from start to goal.
	Note that the letters s and g overwrite the * symbols from the
	corresponding cells. If the start and the goal are
	the same cell, then the cell should be marked with g.
	If there is no path, throw "No path from start to goal".
	*/
	void outputPath(std::ostream& o);



	/* Outputs the navigation directions for the path from 
	the start to the goal position as a sequence of 
	instructions of the following form:
	move from (X1,Y1) to (X1,Y2)
	turn North
	turn South
	turn East
	turn West
	You have arrived at your destination.
	

	For example, for the example above, it should output

	Move from (0,0) to (2,0).
	Turn North.
	Move from (2,0) to (2,2).
	Turn West.
	Move from (2,2) to (0,2).
	You have arrived at your destination.

	The output should not contain empty lines.
	If there is no path, throw "No path from start to goal".

	If start and goal are the same, should just output
	You have arrived at your destination.
	*/
	void outputDirections(std::ostream& o);


private:
	
	// Variables to use when going moving in the grid.
	static const int NORTH = 1, EAST = 1, SOUTH = -1, WEST = -1;

	// I and J are values that represent the diemensions of the grid.
	int I, J;

	// We keep track which is the start and end values and all other
	// cells are: std::pair<int, int> cell;
	std::pair<int, int> start, end;
	std::pair<int, int> cell;

	// Represents if the cell is blocked or not
	bool blockSpace;

	// The grid will be stored as a map, with each cell having attributes relating to it.
	// Each cell has a unique value. Values with number:
	// 0: Not Blocked
	// 1: Blocked
	// 2: Path to Goal
	std::map<std::pair<int, int>, int> grid;

	// A set to prevent backtracking while searching a path in a grid.
	std::set<std::pair<int, int>> visited;

	/*
	Stores the path to take to get to the goal.
	*/
	std::list<std::string> pathList;

	/*
	The stack checks the path taken and prevents the search from going back
	on itself. e.g. if the most recent path taken is south then do not
	go north (opposite direction)
	*/
	std::stack<std::string> pathChecker;

	/*
	This is a private function which performs a depth first search on the grid
	to find the goal. The algorithm is recursive and searches with a NORTH bias
	first, thus there is some in-efficiency when searching the best path.

	We can alter the search by adding another condition to test for the best cell
	(closest cell) to the goal.
	*/
	std::list<std::string> depthFirstSearch(std::pair<int, int> nextCell);

	// Private functions for reading the file, which sections off most of the
	// reading to these extra functions for readablility and debugging.
	void readStart(std::string& line, int& first, int& second);
	void readGoal(std::string& line, int& first, int& second);
};


#endif /* GRID_H_ */
