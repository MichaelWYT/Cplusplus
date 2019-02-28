#ifndef MYSET_H_
#define MYSET_H_

#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

using std::vector;
using std::set;
using std::cout;
using std::endl;


/* In this exercise you will use templates to implement a container
 * which represents a set of elements of some type T.
 * The type T is assumed to have copy constructors and assignment
 * operators implemented for it, and, furthermore, operator<, operator==,
 * operator<< and operator>> are overloaded for type T.
 *
 *
 * You are advised to use the STL containers for storing
 * information. This should help you implement this class.
 *
 * The container accepts objects of type T and stores them. 
 * It allows for searching for a value in the set, 
 * and if the value is not present, it returns a vector consisting
 * of the greatest K elements smaller than that value, followed by the
 * smallest K elements greater than that value. 
 * It also allows you to get a vector of all elements of the set
 * that are between a given start value and a given end value.
 * In either case, the elements in the returned vector should be sorted
 * in ascending order, according to the operator <.
 *
 * Details about each of the functions of Set are given below.
 */

template<class T>
class Set {
public:
	// Default constructor initializing an empty container
	Set();

	// Destructor
	~Set();

	// No need to implement copy and move constructors
	Set(const Set&) = delete;
	Set(Set&&) = delete;
	// No need to implement assignment operators
	Set& operator=(const Set& other) = delete;
	Set& operator=(Set&& other) = delete;

	// Populates the set from a file. We assume 
	// that operator>> is defined for the type T.
	// If the file cannot be open or there is an error
	// during reading, throws std::exception.
	// If the container already contains some elements,
	// they are all dropped before reading the file.
	void readFromFile(const std::string& file_name);

	
	// Searches for value val in the container. 
	// If val is found in container, returns a vector
	// of length 1 containing this single value. 
	// If val is not found in the container, returns a 
	// vector (l_1,...,l_i,g_1,...g_j), 
	// where l_1, ..., l_i are the largest K elements of the 
	// set that are smaller than val,
	// and g_1, ... g_j are the smallest K elements of the 
	// set that are greater than val.
	// If the container contains fewer than K elements smaller 
	// than val, then l_1, ..., l_i are all the elements
	// of the set that are smaller than val.
	// If the container contains fewer than K elements greater 
	// than val, then g_1, ..., g_j are all the elements
	// of the set that are greater than val.
	// Furthermore, the elements of the returned vector should
	// be ordered in ascending order according to <, that is:
	// l_1 < ...< l_i < g_1 < ... < g_j.
	std::vector<T> findClosest(const T& val, unsigned int K) const;

	
	// Returns all the elements of the set container that are greater
	// or equal to start_value and smaller or equal to end_value. 
	// The elements of the returned vector should be in ascending order 
	// according to <. That is, the returned vector is (e_1,...,e_n), where:
	// -- we have e_1 < e_2 < ...< e_n.
	// -- all elements of set that are greater or equal to start_value
	// AND are smaller or equal to end_value are among e_1,...,e_n.
	// If start_value > end_value, then the returned vector should be empty.
	// Note that start_value and end_value do not have to exist in the container.
	std::vector<T> getRange(const T& start_value,const T& end_value) const;


	// Inserts an element val in the container. 
	// If val is already in the container, does nothing and returns false,
	// otherwise adds val to the container and returns true.
	bool insert(const T& val);
	
	// Removes an element val from the container. 
	// If val is not in the container, does nothing and returns false,
	// otherwise, removes val from the container and returns true.
	bool remove(const T& val);

	// Removes from the container all elements greater or equal to val. 
	// If nothing is removed, returns false, otherwise returns true.
	// Note that even when val is not in the container, elements
	// greater than it have to be removed.
	bool removeGreaterOrEqual(const T& val);

	// Removes from the container all elements smaller or equal to val. 
	// If nothing is removed, returns false, otherwise returns true.
	// Note that even when val is not in the container, elements
	// smaller than it have to be removed.
	bool removeLessOrEqual(const T& val);

	// Returns true if the set is empty, and false otherwise.
	bool empty()const;

	// Returns the number of elements in the set.
	unsigned int size() const;

	// Removes all elements from the set container.
	// Leaves the set empty (with a size of 0).
	void clear();

	// Outputs all the elements of the container in ascending order according to <.
	// We assume that operator<< is overloaded for type T.
	template <class U>
	friend std::ostream& operator<<(std::ostream& o, const Set<U>& dict);


private:
	// We can use any STL container so, I will use a set to represent this Set class
	// Create an empty set when Set class is called.
	set<T> mySet;
};

template<class T> 
Set<T>::Set() {
	// Initialises an this class with its variables to be empty. mySet will be
	// empty when this class is initialised.
}


template<class T> 
Set<T>::~Set(){
}

template<class T>
void Set<T>::readFromFile(const std::string& file_name){
	T word;

	// We clear elements in the set if there are elements inside already.
	if (!mySet.empty()) mySet.clear();

	try {

		// We open the file and read it, we assume the file elements are seperated by white spaces.
		std::ifstream inFile;
		inFile.open(file_name);

		// Keep reading lines until EOF
		while (inFile >> word) {

			// We can assume that the data type are all the same for the file, otherwise
			// the reading of the file fails.
			mySet.insert(word);
		}

		// Close our input file stream, to prevent errors and release system resources.
		inFile.close();
	} catch (std::exception& e) {

		// Any errors reading the file, the message will output.
		cout << "Exception: " << e.what()<<endl;
	}
}

template<class T> 
std::vector<T> Set<T>::findClosest(const T& val, unsigned int K) const{
	vector<T> tempVector;
	int pos(0);

	// If we can find the value then we return the vector with that value of size 1.
	if (mySet.find(val) != mySet.end()) {
		tempVector.resize(1);
		tempVector[0] = val;
		return tempVector;
	} 

	// If K (to look both sides for the value in the set) is larger than the mySet.size()
	// we can just put everything in our set into the vector.
	if (K >= mySet.size()) {
		for (auto it = mySet.begin(); it != mySet.end(); it++) {
			tempVector.resize(mySet.size());
			tempVector[pos] = *it;
			pos++;
		}
		return tempVector;
	}

	int counter(0);
	set<T> tempSetSmall;
	set<T> tempSetBig;

	// We search backwards to find the elements < value.
	// The loop stops if we hit the begining of the set (mySet.rend())
	for (auto it = mySet.rbegin(); it != mySet.rend(); it++) {

		// Adds the value to a tempSet
		if (*it < val && counter < K) {
			tempSetSmall.insert(*it);
			counter++;
		}
	}

	counter = 0;

	// Does the same as the previous loop but checks for larger vals
	for (auto it = mySet.begin(); it != mySet.end();it++) {
		if (*it > val && counter < K) {
			tempSetBig.insert(*it);
			counter++;
		}
	}

	// Resize the vector to both of the sets and then adds them to the vector via a union of both sets.
	tempVector.resize(tempSetSmall.size()+ tempSetBig.size());
	std::set_union(tempSetSmall.begin(), tempSetSmall.end(), tempSetBig.begin(), tempSetBig.end(), tempVector.begin());

	return tempVector;
}


template<class T> 
std::vector<T> Set<T>::getRange(const T& start_value,const T& end_value) const{
	vector<T> tempVector;
	
	// Track the end of the vector
	int pos(0);
	
	// Returns an empty vector if the condition is true.
	if (start_value > end_value) return tempVector;

	// Loops through the set and checks the range of each value in the set.
	for (auto it = mySet.begin(); it != mySet.end(); it++) {
		if (start_value <= *it && *it <= end_value) {
			tempVector.resize(tempVector.size()+1);
			tempVector[pos] = *it;
			pos++;
		}
	}
	return tempVector;
}

template<class T>
bool Set<T>::insert(const T& val){
	/*
	Inserts the given value (val) into the set, as long as it does not exist
	in the set; return true. Otherwise return false.

	mySet automatically increases its size when inserting elements.
	*/

	// Otherwise check if the value exists in the set and return false if it does.
	if (mySet.find(val) != mySet.end()) return false;

	// We can insert if the value doesn't exist in the set.
	mySet.insert(val);
	return true;

}

template<class T>
bool Set<T>::remove(const T& val){
	
	// Similar to insert method, but we check if we can remove (erase)
	// the element.
	
	// This condition means if the value cannot be found, then return false.
	if (mySet.find(val) == mySet.end()) return false;

	// If we can find it then we can remove it from the set and return true.
	mySet.erase(val);
	return true;
	
}

template<class T>
bool Set<T>::removeGreaterOrEqual(const T& val){
	// Variable to check if any values have been removed.
	bool removed=false;

	for(auto it = mySet.begin(); it != mySet.end(); it++){
		
		// Go through the iteration and removes each value where it's >=.
		// Iterator is a pointer so we dereference for the value.

		// Remove value if *it is greater than or equal to the value.
		if(*it >= val) removed=remove(*it);
	}
	// If no values have been removed, it returns its default value false.
	return removed;	
}


template<class T>
bool Set<T>::removeLessOrEqual(const T& val){

	// Same as removeGreaterOrEqual, but the condition has changed and we
	// loop through the list in reverse order.
	bool removed=false;
	for (auto it = mySet.rbegin(); it != mySet.rend(); it++) { 
		if (*it <= val) removed = remove(*it); 
	}
	return removed;	
}

template<class T>	
bool Set<T>::empty()const{
	return mySet.empty();	
}

template<class T>
unsigned int Set<T>::size() const{
	return mySet.size();
}

template<class T>
void Set<T>::clear(){
	mySet.clear();
}

template<class T>
std::ostream& operator<<(std::ostream& o, const Set<T>& s){
	o << "{";
	for (auto it = s.mySet.begin(); it != s.mySet.end(); it++) {
		o << *it;
		// Looks ahead by 1 to see if it is the end of the set.
		// This is used for formatting purposes.
		if (std::next(it,1) != s.mySet.end()) o << ", ";
	}
	return o << "}"<<endl;
}


#endif /* MYSET_H_ */
