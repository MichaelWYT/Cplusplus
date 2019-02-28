#include "Grid.h"
#include <ctype.h>
#include <exception>
#include <algorithm>
#include <utility>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;

// Empty grid STL and diemensions to 0.
Grid::Grid() : I(0), J(0) {
}

Grid::~Grid(){
}

void Grid::loadFromFile(const std::string& filename) {
	string line;
	vector<string> posOnGrid;
	int startFirst(0), startSecond(0), goalFirst(0), goalSecond(0);
	std::ifstream inFile(filename);

	// If the file can be opened, it means it can find the file and it exists
	if (inFile.is_open()) {
		try {

			// We read the first 2 lines to find the start and end points
			// First line: START(X1,Y1)
			std::getline(inFile, line);
			readStart(line, startFirst, startSecond);

			// Second line: GOAL(X2,Y2)
			std::getline(inFile, line);
			readGoal(line, goalFirst, goalSecond);

			// Read the first line to determine the width of the grid.
			std::getline(inFile, line);

			// If we don't have a grid position in the file we fail the read.
			if(line.empty()) throw string("Error loading grid description");

			// Otherwise, we carry on read the file.
			I = line.length(); J = 1;

			// Put the line in the temp vector.
			posOnGrid.push_back(line);

			/* 
			Different OS's have different line endings on each new line
			- windows: \r\n 
			- Linux: \n 
			- Macs: \r

			Assuming that the code will be running on linux with a LF line
			ending and not CRLF we do not need to remove the \r.

			Here I converted the DOS txt file into a unix txt.
			*/

			// We then read the rest of the file
			while (std::getline(inFile, line)) {

				// We check if the length of each row is the same as the first.
				if(line.length() != I) throw string("Error loading grid description");

				// Add it to the temp vector
				posOnGrid.push_back(line);

				// Increase depth after a successfull read.
				J++;
			}

			// Mini test to see the grid in the file
			//for (int i(0); i < 3; i++) {
			//	std::cout << posOnGrid[i] << std::endl;
			//}

			// Reverse the vector so the last line is on the top of the vector.
			std::reverse(posOnGrid.begin(), posOnGrid.end());

			// Mini test to see the grid in the file.
			//for (int i(0); i < 3; i++) {
			//	std::cout << posOnGrid[i] << std::endl;
			//}

			// We can set the start and goal values
			setStart(startFirst, startSecond);
			setGoal(goalFirst, goalSecond);

			/* 
			By reading the rest of the file we found the depth of the grid.
			We have the map of the grid in the vector, this is done as we can
			read the file in reverse order or from top to bottom. 
			
			But we have it in a neat and easy to access container to loop 
			through and	manipulate the string to put pair<int,int> into 
			our map following the vector data.
			*/
			
			// Nested loop to go row by row adding data to our map column by column
			// We look at the bottom of the grid (first vector position) as we reversed it
			// and read left to right, accending order.
			for (int j(0); j < J; j++) {
				for (int i(0); i < I; i++) {

					// If the character at pos i is either 'o' or 'x' then we add a pair to the
					// map with true/false value if it's blocked. Any other un recognised key fails.
					if (posOnGrid[j].at(i) == 'o') {
						grid[std::make_pair(i, j)] = 0;
					} else if(posOnGrid[j].at(i) == 'x') {
						grid[std::make_pair(i, j)] = 1;
					} else {
						throw string("Error loading grid description");
					}
				}
			}

			/*
			Note: The map stores the pairs in acending order comparing the j-value
			thus, iterating through you get (0,0), (0,1), (0,2) etc. instead of 
			by row i.e. (0,0), (1,0) etc. via i-value
			*/

			/*for (auto it = grid.begin(); it != grid.end(); it++) {
				std::cout << "(" << it->first.first<< ","<<it->first.second<<"), ";
			}*/
		} catch (string& e) {
			throw string("Error loading grid description");
		} catch (std::exception& e) {
			throw string("Error loading grid description");
		}

	} else {
		throw string("Error loading grid description");
	}

	inFile.close();
}

bool Grid::isStart(int x,int y) const{
	// Check if the x,y are out of bounds then check if its a node.
	if(x >= I || y >= J || x < 0 || y < 0) throw string("Position outside of the range of the grid.");
	
	// Checks if the given values are the same as the start values.
	if (start.first == x && start.second == y) return true;
	return false;

}
bool Grid::isGoal(int x,int y) const{
	// Same condition as isStart(), but for the end node (Goal)
	if (x >= I || y >= J || x < 0 || y < 0) throw string("Position outside of the range of the grid.");
	if (end.first == x && end.second == y) return true;
	return false;

}
bool Grid::blocked(int x, int y) const{
	if (x >= I || y >= J || x < 0 || y < 0) throw string("Position outside of the range of the grid.");
	
	// Finds the value in the map and checks if the value is blocked or not
	if (grid.find(std::make_pair(x, y))->second == 1) return true;
	return false;
}
void Grid::setStart(int x, int y) {
	if (x >= I || y >= J || x < 0 || y < 0) throw string("Position outside of the range of the grid.");
	start = std::make_pair(x,y);
}

void Grid::setGoal(int x, int y){
	if (x >= I || y >= J || x < 0 || y < 0) throw string("Position outside of the range of the grid.");
	end = std::make_pair(x, y);
}

void Grid::unblock(int x, int y){
	if (x >= I || y >= J || x < 0 || y < 0) throw string("Position outside of the range of the grid.");
	grid.find(std::make_pair(x, y))->second = 0;
}
void Grid::block(int x, int y){
	if (x >= I || y >= J || x < 0 || y < 0) throw string("Position outside of the range of the grid.");
	grid.find(std::make_pair(x, y))->second = 1;
}
bool Grid::existsPath(){

	// Checks if the start or goal are not blocked.
	if (grid.find(start)->second == false && grid.find(end)->second == false) {
		visited.clear();
		pathChecker.push("START");
		pathList = depthFirstSearch(start);
		if (pathList.back() == "GOAL") {
			return true;
		}
	}
	return false;
}
void Grid::outputPath(std::ostream& o){
	// Copy the pathList into path to remove elements.
	list<string> path = pathList;
	std::pair<int, int> nextCell = start;

	// Get rid of the GOAL string ending
	path.pop_back();
	if (existsPath()) {
		/*
		We change the values of the key to 2 from the start to indicate the path
		. Then output it to the stream to be printed.
		*/
		while (!path.empty()) {
			if (path.front() == "N") {
				nextCell = std::make_pair(nextCell.first, nextCell.second+NORTH);
				grid.find(nextCell)->second = 2;
			}
			if (path.front() == "E") {
				nextCell = std::make_pair(nextCell.first+EAST, nextCell.second);
				grid.find(nextCell)->second = 2;
			}
			if (path.front() == "S") {
				nextCell = std::make_pair(nextCell.first, nextCell.second + SOUTH);
				grid.find(nextCell)->second = 2;
			}
			if (path.front() == "W") {
				nextCell = std::make_pair(nextCell.first+WEST, nextCell.second);
				grid.find(nextCell)->second = 2;
			}

			// Every read of the path we pop it from the list.
			path.pop_front();
		}

		// Goes through top to bottom, left to right printing out the grid with path.
		for (int j(J-1); j >= 0;j--) {
			for (int i(0); i < I;i++) {
				nextCell = std::make_pair(i,j);
				if (grid.find(nextCell)->first == start) {
					if (start == end) {
						o << "g";
					}
					else {
						o << "s";
					}
				}
				else if (grid.find(nextCell)->first == end) {
					o << "g";
				}
				else if (grid.find(nextCell)->second == 0) {
					o << "o";
				}
				else if (grid.find(nextCell)->second == 1) {
					o << "x";
				}
				else {
					o << "*";
				}
			}
			o << "\n";
		}
	} else {
		throw string("No path from start to goal");
	}
}
void Grid::outputDirections(std::ostream& o){
	// Temp list to remove elements, so we know we have gone through the path.
	list<string> path = pathList;

	// Hold the most recent direction from path;
	string mostRecent = "";

	// Holds the current cell postion to move from, to get to the new position.
	std::pair<int, int> baseCell = start;
	std::pair<int, int> nextCell = baseCell;

	if (existsPath()) {

		// Ignore the rest of the code and just output to stream.
		if (start == end) {
			o << "You have arrived at your destination.\n";
		}
		else {
			while (!path.empty()) {
				mostRecent = path.front();
				path.pop_front();

				// Move to the nextCell first
				if (mostRecent == "N") {
					nextCell = std::make_pair(nextCell.first, nextCell.second + NORTH);
				}
				if (mostRecent == "E") {
					nextCell = std::make_pair(nextCell.first + EAST, nextCell.second);
				}
				if (mostRecent == "S") {
					nextCell = std::make_pair(nextCell.first, nextCell.second + SOUTH);
				}
				if (mostRecent == "W") {
					nextCell = std::make_pair(nextCell.first + WEST, nextCell.second);
				}

				// If direction has changed we print out the move sequence and change direction.
				if (mostRecent != path.front()) {
					o << "Move from (" << baseCell.first << "," << baseCell.second;
					o << ") to (" << nextCell.first << "," << nextCell.second <<").\n";
					if (path.front() == "N") o << "Turn North.\n";
					if (path.front() == "E") o << "Turn East.\n";
					if (path.front() == "S") o << "Turn South.\n";
					if (path.front() == "W") o << "Turn West.\n";
					if (path.front() == "GOAL") {
						o << "You have arrived at your destination.\n";
						path.pop_front();
					} else baseCell = nextCell;
				}
			}
		}
	} else {
		throw string("No path from start to goal");
	}
}
std::list<string> Grid::depthFirstSearch(std::pair<int,int> nextCell) {
	list<string> list;
	/*
	Go each direction until the goal is found. When it's found return the direction
	to get there recursivley.

	For each direction as long as it's not blocked or out of bounds, go that
	direction
	*/

	// Do not explore this path is visited. Pop stack and return empty list.
	if (visited.find(nextCell) == visited.end()) {

		// To prevent loops in the paths we add the cell as being visisted.
		visited.insert(nextCell);

		/*
		If the cell is the goal then we add the respective direction and end inidicator.
		This is the base case.
		*/
		if (nextCell == end) {
			list.push_back("GOAL");
			return list;
		}
		try {

			// Prevent back tracking while searching a path.
			if (pathChecker.top() != "S") {

				/*
				We check if the next direction can be made and if we can we explore that side of the
				grid. Checking if the cell is blocked or within bounds.

				When the path has been explored and something is returned, then we append the list
				(merge function) returned to the stack ONLY if it has the end indicator on it.
				added from the base case.

				Empty lists returned means that there is no path. A list reaching the goal WILL return
				the end point, therefore we can record the direction into the list.

				As the list will have the end goal all other directions will record their directions
				until all directions from the stack in memory has been poped.
				*/
				if (blocked(nextCell.first, nextCell.second + NORTH) == false) {
					// Push the path on the stack
					pathChecker.push("N");
					list.merge(depthFirstSearch(std::make_pair(nextCell.first, nextCell.second + NORTH)));
					if (list.back() == "GOAL") {
						list.push_front("N");
						return list;
					}

					// If the direction failed, we pop it from the list.
					pathChecker.pop();
				}
			}
		}
		catch (string s) {}
		try {
			if (pathChecker.top() != "W") {
				if (blocked(nextCell.first + EAST, nextCell.second) == false) {
					pathChecker.push("E");
					list.merge(depthFirstSearch(std::make_pair(nextCell.first + EAST, nextCell.second)));
					if (list.back() == "GOAL") {
						list.push_front("E");
						return list;
					}
					pathChecker.pop();
				}
			}
		}
		catch (string s) {}
		try {
			if (pathChecker.top() != "N") {
				if (blocked(nextCell.first, nextCell.second + SOUTH) == false) {
					pathChecker.push("S");
					list.merge(depthFirstSearch(std::make_pair(nextCell.first, nextCell.second + SOUTH)));
					if (list.back() == "GOAL") {
						list.push_front("S");
						return list;
					}
					pathChecker.pop();
				}
			}
		}
		catch (string s) {}
		try {
			if (pathChecker.top() != "E") {
				if (blocked(nextCell.first + WEST, nextCell.second) == false) {
					pathChecker.push("W");
					list.merge(depthFirstSearch(std::make_pair(nextCell.first + WEST, nextCell.second)));
					if (list.back() == "GOAL") {
						list.push_front("W");
						return list;
					}
					pathChecker.pop();
				}
			}
		}
		catch (string s) {}
	}
	
	/*
	If all directions are invalid then we go back to the previous stack in memory.
	*/
	if (!pathChecker.empty()) {
		pathChecker.pop();
	}

	/*
	If all directions have been exhausted, return an empty list with no direction.
	*/
	return list;
}
void Grid::readStart(std::string& line, int& first, int& second) {
	string tempStr;
	int i(0), j(1);

	tempStr = line.substr(0, 5);

	// Then we check if the format for the first line is correct.
	if (tempStr != "START") throw string("Error loading grid description");
	tempStr.clear();

	while (isdigit(line[6 + i]) && line[6 + i] != ',') {
		tempStr += line[6 + i];
		i++;
	}
	first = std::stoi(tempStr);
	tempStr.clear();
	while (isdigit(line[6 + i + j]) && line[6 + i + j] != ')') {
		tempStr += line[6 + i + j];
		j++;
	}
	second = std::stoi(tempStr);
}
void Grid::readGoal(std::string& line, int& first, int& second) {
	string tempStr;
	int i(0), j(1);
	tempStr = line.substr(0, 4);

	if (tempStr != "GOAL") throw string("Error loading grid description");
	tempStr.clear();

	while (isdigit(line[5 + i]) && line[5 + i] != ',') {
		tempStr += line[5 + i];
		i++;
	}
	first = std::stoi(tempStr);
	tempStr.clear();
	while (isdigit(line[5 + i + j]) && line[5 + i + j] != ')') {
		tempStr += line[5 + i + j];
		j++;
	}

	second = std::stoi(tempStr);
}