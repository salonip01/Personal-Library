#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void readMyLibData(string filename, vector<string>& lines);
/*Parameters: name of the csv file and a vector of strings (passed in by reference)
 *Returns: void function doesn't return but add books to vector
 */

void addBook(vector<string>& lines, string ipt, string& filename);
/*Parameters: vector with the data, details of the book which is to be added
 * and the name of the csv file
 */

void writeToFile(vector<string>& lines, string& filename);
/*Parameters: vector with the data and the csv file to which data will be added
 */

string bookStatus(vector<string> lines, string name);
/*Parameters: vector with the data and the name of the book which is to be searched
 *Returns: the reading status of the book or report if the book isn't added in the csv file
 */

string bookHolder(vector<string> lines, string name);
/*Parameters: vector with the data and the name of the book which is to be searched
 *Returns: the name of the person who currently has the book
 */

void printInfo(vector<string> lines, string name);
/*Parameters: vector with the data and the name of the book which is to be searched
 *Returns: void function but prints the information about the asked book to the screen
 */

void printByAuthor(vector<string> lines, string name);
/*Parameters: vector with the data and the name of the author which is to be searched
 *Returns: void function but prints all the books from a particular author
 */