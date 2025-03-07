#include "myLib.h"

int main() {
    vector<string> libData;
    string filename = "C:/Users/ssp10/CLionProjects/untitled/Personal Library Database/myLibData.csv";
    //replace 'filename' with the directory address
    bool contProg = true;
    int iptInt;
    string iptStr, retStr;

    cout << "\n!!Welcome to Saloni Patel's personal Library Database!!"
         << "\nWhat is the agenda for today?"
         << "\n1.Add a new book to the database"
         << "\n2.Retrieve a book's current status"
         << "\n3.Find a book's current holder"
         << "\n4.Retrieve all information about a book"
         << "\n5.Find all books from a particular author"
         << "\nNOTE: Press -1 to exit";

    readMyLibData(filename, libData); //Copy all books to the vector 'libData'

    while (contProg) {
        cout << "\nWhat would you like to do? ";
        cin >> iptInt;

        switch (iptInt) {
            case -1: //Exit program
                cout << "\nThank you for stopping by."
                     << "\nHappy Reading!"
                     << "\n**Exiting program**";
                contProg = false; //Exit the loop
                break;

            case 1: //Add book to the database
                cout << "\nEnter the details of the book you would like to add to the database."
                     << "\nPlease follow the order and separate each category by only commas no space: "
                     << "\nBook Title->Name of the Author->13 digit ISBN->Read Status->Current Holder";

                cin.ignore(); //Makes sure that cin waits for input string
                getline(cin, iptStr);
                addBook(libData, iptStr, filename);
                break;

            case 2: //Find the status of a book
                cout << "\nPlease enter the name of the book you're looking for: ";
                cin.ignore();
                getline(cin, iptStr);

                retStr = bookStatus(libData, iptStr);
                if (retStr == "Book not found") { //If book not in the file, report to the screen
                    cout << "\nThe book you asked for is not stored in the digital library";
                }
                else {
                    cout << "\nThe status of \"" << iptStr << "\" is: " << retStr;
                }
                break;

            case 3: //Find the current holder of a book
                cout << "\nPlease enter the name of the book you're looking for: ";
                cin.ignore();
                getline(cin, iptStr);

                retStr = bookHolder(libData, iptStr);
                if (retStr == "Book not found") {
                    cout << "\nThe book you asked for is not stored in the digital library";
                }
                else {
                    cout << "\nThe book \"" << iptStr << "\" is with " << retStr;
                }
                break;

            case 4: //Find and print all info about a book
                cout << "\nPlease enter the name of the book you're looking for: ";
                cin.ignore();
                getline(cin, iptStr);

                retStr = bookStatus(libData, iptStr);
                if (retStr == "Book not found") {
                    cout << "\nThe book you asked for is not stored in the digital library";
                }
                else {
                    cout << "\nBOOK DETAILS: ";
                    printInfo(libData, iptStr);
                }
                break;

            case 5: //Find all books from an author
                cout << "Please enter the name of the author you're looking for: ";
                cin.ignore();
                getline(cin, iptStr);

                cout << "Here is a list of all the books by " << iptStr
                     << " that are in Saloni's library: " << endl;

                printByAuthor(libData, iptStr);
                break;


            default:
                cout << "\nERROR: Please choose a valid functionality as per the displayed menu.";

        }
    }
}

void readMyLibData(string filename, vector<string>& lines) {
    string newLine;

    ifstream file(filename);
    if (file.is_open()) {
        while (getline(file, newLine)) {
            lines.push_back(newLine); //Add to the vector
        }
    }

    else {
        cout << "\nERROR: Unable to open file \"" << filename << "\"" //When error in opening file
             << endl;
        return;
    }
    file.close();
}

void writeToFile(vector<string>& lines, string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& l : lines) {
            file << l << endl; //Write all books (with any changes, if made) to the vector
        }
    }

    else {
        cout << "\nERROR: Unable to open file \"" << filename << "\"";
    }
    file.close();
}

void addBook(vector<string>& lines, string ipt, string& filename) {
    bool found = false;

    for (const auto& line : lines) {
        if (line == ipt) {
            found = true; //Book is already in the file
            cout << "\nThe book's data is already stored in the digital library.";
            return;
        }
    }

    if (found == false) { //If not, add it to the vector
        lines.push_back(ipt);
    }
    writeToFile(lines, filename);
}

string bookStatus(vector<string> lines, string name) {
    int ind, ind2;

    for (const auto& l : lines) {
        ind2 = l.find(",");

        if (l.substr(0, ind2) == name) {
            for (int i = 0; i < 3; i++) { //Iterate three times to reach the fourth column
                ind = ind2;
                ind2 = l.find(",", ind + 1);
            }
            return (l.substr(ind + 1, ind2 - ind - 1));
        }
    }
    return "Book not found";
}

string bookHolder(vector<string> lines, string name) {
    int ind, ind2;

    for (const auto& l : lines) {
        ind2 = l.find(",");

        if (l.substr(0, ind2) == name) {
            for (int i = 0; i < 3; i++) { //Iterate three times to reach the index of the last comma
                ind = ind2;
                ind2 = l.find(",", ind + 1);
            }
            return (l.substr(ind2 + 1));
        }
    }
    return "Book not found";
}

void printInfo(vector<string> lines, string name) {
    int ind, ind2, ind3, ind4;
    string categories = lines[0]; //Copy the first line to a string

    for (int i = 1; i < lines.size(); i++) { //Skip the first element and iterate through every other
        ind3 = categories.find(",");
        ind4 = lines[i].find(",");

        if (lines[i].substr(0, ind4) == name) {
            for (int j = 0; j < 4; j++) {
                if (j == 3) { //For the last iteration, just print the remaining string
                    cout << endl << categories.substr(ind3+1)
                         << ": " << lines[i].substr(ind4+1);
                    break;
                }

                else {
                    ind = ind3;
                    ind3 = categories.find(",", ind + 1);

                    ind2 = ind4;
                    ind4 = lines[i].find(",", ind2 + 1);

                    cout << endl << categories.substr(ind + 1, ind3 - ind - 1)
                         << ": " << lines[i].substr(ind2 + 1, ind4 - ind2 - 1);
                }
            }
        }
    }
}

void printByAuthor(vector<string> lines, string name) {
    int ind, ind2;

    for (const auto& l : lines) { //Iterate through all the elements and if the name matches, print
        ind = l.find(",");
        ind2 = l.find(",", ind + 1);

        if (l.substr(ind+1, ind2 - ind - 1) == name) {
            cout << l.substr(0, ind) << endl;
        }
    }
}