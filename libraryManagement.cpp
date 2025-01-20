// ----Library Management ------//

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// library database
class database
{
protected:
    static map<pair<string, int>, pair<int, int>> bookList;
    static map<int, pair<string, string>> studentList;
    static map<string, int> issuedBooks;

public:
    // pure virtual functions
    virtual void displayBooks() {}

    virtual void displayStudentList() {}
};

// Define static members
map<pair<string, int>, pair<int, int>> database::bookList;
map<int, pair<string, string>> database::studentList;
map<string, int> database::issuedBooks;

// librarian
class librarian : public virtual database
{
public:
    string name;
    int emp_Id;

    void addBook(string title, int bookID, int row, int col)
    {
        bookList[{title, bookID}] = {row, col};
    }

    void displayBooks(int id)
    {
        if (id == this->emp_Id)
        {
            if (bookList.empty()) {
                cout << "No books available in the library." << endl;
            } else {
                for (auto it : bookList)
                {
                    cout << "Title: " << it.first.first << ", BookID: " << it.first.second << ", Row: " << it.second.first << ", col: " << it.second.second << endl;
                }
            }
            cout << endl;
        }
        else
        {
            cout << "Un-authorized person!" << endl;
            cout << endl;
        }
    }

    void addStudent(int id, string name, string department)
    {
        studentList[id] = {name, department};
    }

    void displayStudentList(int id)
    {
        if(id == this->emp_Id){
            if (studentList.empty()) {
                cout << "No students registered in the library." << endl;
            } else {
                for (auto it : studentList)
                {
                    cout << "Student_Id: " << it.first << ", Name: " << it.second.first << ", Department: " << it.second.second << endl;
                }
            }
            cout << endl;
        }else{
            cout << "Un-authorized person!" << endl;
        }
    }

    // Check if a book is already issued or not
    bool isBookIssued(string title)
    {
        if (issuedBooks.find(title) != issuedBooks.end())
        {
            cout << "A book is already issued!" << endl;
            return true;
        }
        else
        {
            cout << "The book '" << title << "' is not yet issued." << endl;
            return false;
        }
    }
    
    // Issue book to a student
    void issueBook(string title, int bookId, int student_ID){

        // check whether the book is present or not
        if(bookList.find({title, bookId}) == bookList.end()){
            cout << "The book '" << title << "' does not exist in the library." << endl;
            return;
        }

        // check if it is already issued to given student
        if(isBookIssued(title)){
            cout << "Cannot issue! The book '" << title << "' is already issued!" << endl;
            return;
        }
        
        // Issue the book to the student
        issuedBooks[title] = student_ID;
        cout << "The book '" << title << "' has been issued to student with ID: " << student_ID << endl;

        // Provide the location
        auto location = bookList[{title, bookId}];
        cout << "Please collect the book from row: " << location.first << ", column: " << location.second << endl;
        
        // Remove the book from available list
        bookList.erase({title, bookId});    
    }


    // Return a book
    void returnBook(string title, int bookId, int row, int col){

        // Check if the book is issued
        if (issuedBooks.find(title) == issuedBooks.end()) {
            cout << "The book '" << title << "' is not issued, so it cannot be returned." << endl;
            return;
        }

        // Remove the book from issuedBooks
        issuedBooks.erase(title);


        // Add the book back to bookList
        bookList[{title, bookId}] = {row, col};
        cout << "The book '" << title << "' has been successfully returned." << endl;
        
    }
};

// student
class student : public virtual database
{
public:
    string Name;
    int scholar_Id;
    string department;

    // Display books (accessible to all students)
    void displayBooks(int id) {
        if (studentList.find(id) == studentList.end()) {
            cout << "You are not our college student!" << endl;
        } else {
            if (bookList.empty()) {
                cout << "No books available in the library." << endl;
            } else {
                cout << "Available Books:\n";
                for (auto it : bookList) {
                    cout << "Title: " << it.first.first << ", BookID: " << it.first.second
                         << ", Row: " << it.second.first << ", Col: " << it.second.second << endl;
                }
            }
            cout << endl;
        }
    }
};

void displayWelcomeMessage() {
    cout << "=======================================" << endl;
    cout << "    Welcome to Library Management System    " << endl;
    cout << "=======================================" << endl;
    cout << "Please choose an option from the menu below:\n";
}

void librarianMenu(librarian *l1) {
    int choice;
    do {
        cout << "\nLibrarian Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Add Student\n";
        cout << "4. Display Student List\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title;
                int bookID, row, col;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book ID: ";
                cin >> bookID;
                cout << "Enter row: ";
                cin >> row;
                cout << "Enter column: ";
                cin >> col;
                l1->addBook(title, bookID, row, col);
                break;
            }
            case 2:
                l1->displayBooks(l1->emp_Id);
                break;
            case 3: {
                int id;
                string name, department;
                cout << "Enter student ID: ";
                cin >> id;
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter department: ";
                getline(cin, department);
                l1->addStudent(id, name, department);
                break;
            }
            case 4:
                l1->displayStudentList(l1->emp_Id);
                break;
            case 5: {
                string title;
                int bookID, studentID;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book ID: ";
                cin >> bookID;
                cout << "Enter student ID: ";
                cin >> studentID;
                l1->issueBook(title, bookID, studentID);
                break;
            }
            case 6: {
                string title;
                int bookID, row, col;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book ID: ";
                cin >> bookID;
                cout << "Enter row: ";
                cin >> row;
                cout << "Enter column: ";
                cin >> col;
                l1->returnBook(title, bookID, row, col);
                break;
            }
            case 7:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);
}

void studentMenu(student *s, int studentId) {
    int choice;
    do {
        cout << "\nStudent Menu:\n";
        cout << "1. Display Books\n";
        cout << "2. Exit to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s->displayBooks(studentId);
                break;
            case 2:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 2);
}

int main()
{
    int userType;
    librarian *l1 = new librarian();
    l1->name = "Mr. Kapil Sharma";
    l1->emp_Id = 100;

    student *s1 = new student();
    s1->scholar_Id = 2112137;

    do {
        displayWelcomeMessage();
        cout << "Select user type:\n1. Librarian\n2. Student\n3. Exit\nEnter your choice: ";
        cin >> userType;

        if (userType == 1) {
            librarianMenu(l1);
        } else if (userType == 2) {
            int studentId;
            cout << "Enter your student ID: ";
            cin >> studentId;
            studentMenu(s1, studentId);
        } else if (userType == 3) {
            cout << "Exiting Library Management System. Goodbye!\n";
            break;
        } else {
            cout << "Invalid user type! Try again.\n";
        }
    } while (userType != 3);

    return 0;
}

