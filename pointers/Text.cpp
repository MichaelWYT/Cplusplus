#include <iostream>     
#include <string>     

#include "Text.h"

using std::string;
using std::ostream;

void resize(string*& text, uint length, uint& capacity, uint new_capacity){
	if (new_capacity > capacity) {
		// Creates a temporary pointer to the new array in dynamic memory.
		string* temp = new string[new_capacity];
		for(uint i=0;i<length;i++){
			temp[i] = text[i];
		}

		// After setting capacity to the new capacity, delete the old array 
		// from dynamic memory and point to the new one.
		capacity = new_capacity;
		delete [] text;
		text = temp;
	}

}

string* readText(istream& in, uint& length, uint& capacity){
	// Initialise the variables:
	// Length set to 0 to count the number of words from the instream.
	length = 0;

	// Temporary variable to store the word from instream and pointer to a array in dyn. memory.
	string word="";
	string* words = new string[capacity];

	// Loop through the stream until "EOT" is reached.
	do {
		in >> word;
		if(word != END_OF_TEXT){

			// Each loop, we check if we need to expand the capacity of our array
			if(capacity <= length){
				resize(words, length, capacity, capacity+2);
			}

			// Increase the counter for length and add the word to the array.
			length++;
			words[length-1] = word;
		}
	} while (word != END_OF_TEXT);

	return words;
}


void outputText(ostream& out, const string* text, uint length){

	// On the same line output the text to terminal
	for(uint i = 0; i < length;i++){
		out << text[i] << " ";
	}

	// End the stream.
	out << "\n";
}

void appendText(string*& text, uint& length, uint& capacity, 
		const string * const other, uint length_other){

	uint totalLength = length+length_other;

	// Resize the array if the combined length is bigger than the array size.
	if(totalLength > capacity){
		resize(text, length, capacity, length+length_other);
	}

	// Add contents of the other aray to the array.
	for(uint i = 0;i < length_other;i++){
		text[length+i] = other[i];
	}

	// Finally, we update the length, capacity has already been updated.
	length += length_other;
}


bool containsWord(const string *text, uint length, const string& word){

	// Loops through the entire array until the word is found, otherwise returns false.
	for(uint i=0;i<length;i++){
		if(text[i] == word){
			return true;
		}
	}

	// If empty array or no words found, return false.
	return false;
}

uint wordCount(const string *text, uint length, const string& word){

	// Increment the counter when the word is found.
	uint count=0;
	for(uint i=0;i<length;i++){
		if(text[i] == word){
			count++;
		}
	}
	return count;
}

string* getWords(const string *text, uint length, uint& number_unique, uint& capacity_unique){

	// Initialise "unique" array to store words.
	string* unique = new string[capacity_unique];

	// Loop through text array, to find unique words.
	for(uint i=0;i<length;i++){

		// Check if the word is already stored in the array.
		if(!containsWord(unique,number_unique,text[i])){

			// Resize the array if the capacity is smaller or equal than the number of unique words.
			if (capacity_unique <= number_unique) {
				resize(unique, number_unique, capacity_unique, capacity_unique + 1);
			}

			// Increment the number_unique and add the word.
			number_unique++;
			unique[number_unique-1] = text[i];
		}
	}

	return unique;
}

void replaceWordAll(string*& text, uint length, const string& word, const string& new_word){
	
	// Loop through text array and overwrite value at [i] to the new_word.
	for(uint i=0;i<length;i++){
		if(text[i] == word){
			text[i] = new_word;
		}
	}

}

void deleteWordAll(string*& text, uint& length, const string& word){

	uint counter(0);
	string* temp = new string[length];

	/*
	Copy everything into the temp array without words we need to delete.

	Then overwrite everthing in the text array with temp.

	Anything after the array will be set to null ("").

	Set new length to the counter.

	Deallocate the memory that temp is using, as we copied the items we needed.
	*/
	for(uint i=0;i<length;i++){
		if(text[i] != word){
			counter++;
			temp[counter-1] = text[i];
		}
	}

	for (uint j=0;j<length;j++) {
		if (j<counter) {
			text[j] = temp[j];
		}
		else {
			text[j] = "";
		}
	}
	length = counter;
	delete [] temp;
}

void replacePhraseFirst(string*& text, uint& length, uint& capacity,
		const string *phrase, uint phrase_length,
		const string *new_phrase, uint new_phrase_length){

	/*
	Double loop through the text array once and again to check the phrase.

	While the word is not the the phrase we seek we add it to the temp array.

	Once the phrase is found, add the new phrase to the temp array then add the rest of...
	the text array not apart of the phrase to the text array.

	Then copy over the contents to the other array.
	*/

	bool change = false;
	uint templength = 0;

	// If text array or the phrase is empty, we don't do anything.
	if (length != 0 && phrase_length != 0) {
		// Length changes when phrase_length new and old are different.
		// If lengths are the same it makes no difference as they would cancel out (==0)
		// e.g. PL=6;NPL=6; NPL-PL=0;
		templength = length + (new_phrase_length - phrase_length);

		// If the new length (length+new)
		if (templength > capacity) {
			resize(text, length, capacity, templength);
		}

		string* temp = new string[templength];

		// We know that the phrase is inside text array.
		if(length >= phrase_length){
			for (uint i = 0; i < length; i++) {

				// If the word/letter starts the same as the phrase we check the sequence after it.
				if (text[i] == phrase[0]) {

					for (uint j = 0; j < phrase_length; j++) {

						// This means that there would be no occurence of the word: array out of bounds
						if (i+j <= length) {
							if (text[i + j] == phrase[j]) {

								// As long as the phrase is the one we are looking for keep it true.
								change = true;
							}
							else {

								// Otherwise, break from the for loop and change back to false.
								change = false;
								break;
							}
						}
					}
				}
				if (change) {

					// Add the new phrase into the temp array.
					for (uint k = 0; k < new_phrase_length; k++) {
						temp[i + k] = new_phrase[k];
					}

					// Then add the rest of text to the temp array
					for (uint c = 0; c < length-phrase_length-i; c++) {
						temp[i + new_phrase_length + c] = text[i + phrase_length + c];
					}

					// Then break from the outer loop.
					break;
				}
				else {

					// If the words don't match up to the new phrase add it to the temp array.
					temp[i] = text[i];
				}

			}

			// Finally, copy over the contents
			for (uint j = 0; j < capacity; j++) {
				// If templength is smaller than length then it will fill the gaps at the end with ""
				// Otherwise the array will be full with copied contents.

				if (templength < length && j > templength) {
					text[j] = "";
				}
				else {
					text[j] = temp[j];
				}
			}

			// If text array is resized it's capacity is changed, otherwise we keep capacity the same.
			// The length is always changed or it's the same. Smaller, Bigger, Same.
			length = templength;
		}
	}
}

