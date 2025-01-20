# Library Management System

This is a C++ implementation of a **Library Management System** that allows librarians and students to interact with the library database. The system provides a simple command-line interface for adding, viewing, issuing, and returning books, as well as managing student information.

## Features

### For Librarians:
- **Add Books**: Add books to the library with title, ID, and location details.
- **Display Books**: View all books currently available in the library.
- **Add Students**: Register students to the library database.
- **Display Student List**: View all registered students.
- **Issue Books**: Issue books to students.
- **Return Books**: Return previously issued books back to the library.

### For Students:
- **View Available Books**: View details of all books currently available in the library.

### General:
- Prevents issuing books that are not available.
- Handles invalid inputs and unauthorized access.

## How It Works

### Structure:
1. `database` Class:
   - Manages static data for books, students, and issued books.
   - Acts as a base class for `librarian` and `student` classes.

2. `librarian` Class:
   - Provides functionalities like adding books, managing students, issuing books, and returning books.

3. `student` Class:
   - Allows students to view the list of available books.

4. Main Menu:
   - Presents options for librarians and students to interact with the system.

### Key Functions:
- Librarian Menu:
  - Add books, manage students, issue and return books.
- Student Menu:
  - View available books.
- Validation:
  - Ensures only authorized users access certain features.
  - Validates whether books are available before issuing.



## Example Interaction

```
=======================================
    Welcome to Library Management System
=======================================
Please choose an option from the menu below:
Select user type:
1. Librarian
2. Student
3. Exit
Enter your choice: 1

Librarian Menu:
1. Add Book
2. Display Books
3. Add Student
4. Display Student List
5. Issue Book
6. Return Book
7. Exit to Main Menu
Enter your choice: 1
Enter book title: Harry Potter
Enter book ID: 100
Enter row: 1
Enter column: 2

Returning to main menu...
```



