#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

class Library {
private:
    string book_id;
    string book_name;
    string author_name;
    int no_of_copies;
    int borrowed_copies;
public:
    void control_panel();
    void donate_book();
    void display_books();
    void search_book();
    void borrow_book();
    void return_book();
    void available_books();
    
};
void Library::control_panel()
{
    system("cls");
    cout << "\n\n\t\t\t\tSystem";
    cout << "\n\n1. VIEW BOOKSS:-";
    cout << "\n2. SEARCH BOOKS:-";
    cout <<"\n3  DONATE BOOKS:-";
    cout << "\n4. BORROW  BOOKS:-";
    cout << "\n5. RETURN BOOKS:-";
    cout << "\n6. AVAILABLE BOOKS:-";
    cout << "\n7. EXIT";
}

// Function to add book to the library
void Library::donate_book() {
    fstream file;
    file.open("books.txt", ios::app | ios::out);

    if (!file) {
        cout << "\nError in opening file!!!";
        return;
    }
    cout << "\nEnter Book ID : ";
    cin >> book_id;
    cout << "Enter Book Name : ";
    cin >> book_name;
    cout << "Enter Author Name : ";
    cin >> author_name;
    cout << "Enter Number of Copies : ";
    cin >> no_of_copies;
    borrowed_copies = 0;
    file << book_id << " " << book_name << " " << author_name << " " << no_of_copies << " " << borrowed_copies << endl;
    file.close();
    cout<<"Thank You for your contribution...";
}

// Function to display all books in the library
void Library::display_books() {
struct Book {
string book_id;
string book_name;
string author_name;
int no_of_copies;
int borrowed_copies;
};

fstream file;
file.open("books.txt", ios::in);

if (!file) {
    cout << "Error opening file" << endl;
    return; // return if file cannot be opened
}

Book books[5];
int i = 0;
    cout << "\n-------------------------------------------------------------\n";
    cout << "Book ID \t Book Name \t\t Author Name \t No of Copies \t Available Copies\n";
    cout << "-------------------------------------------------------------\n";

while (i < 5 && file >> books[i].book_id >> books[i].book_name >> books[i].author_name >> books[i].no_of_copies >> books[i].borrowed_copies) {
    i++;
}

file.close();

// Printing the book details
for (int j = 0; j < i; j++) { // loop till the number of books read from the file
    cout << books[j].book_id << " \t " << books[j].book_name << " \t\t " << books[j].author_name << " \t " << books[j].no_of_copies << " \t " << books[j].borrowed_copies << endl;
}
}

// Function to search book by its ID
void Library::search_book() {
    fstream file;
    file.open("books.txt", ios::in);

    if (!file) {
        cout << "\nError in opening file!!!";
        return;
    }
    string search_id;
    cout << "\nEnter Book ID to search : ";
    cin >> search_id;
    int found = 0;
    while (file >> book_id >> book_name >> author_name >> no_of_copies >> borrowed_copies) {
        if (book_id == search_id) {
            found = 1;
            cout << "\n-------------------------------------------------------------\n";
            cout << "Book ID \t Book Name \t\t Author Name \t No of Copies \t Available Copies\n";
            cout << "-------------------------------------------------------------\n";
            cout << book_id << "\t\t " << book_name << "\t\t " << author_name << "\t\t " << no_of_copies << "\t\t " << no_of_copies - borrowed_copies << endl;
        }
    }
    if (found == 0) {
        cout << "\nBook not found!!!";
    }
    file.close();
}
// Function to borrow a book
void Library::borrow_book() {
fstream file, temp;
file.open("books.txt", ios::in);
temp.open("temp.txt", ios::out);
if (!file) {
    cout << "\nError in opening file!!!";
    return;
}
string borrow_id;
int found = 0;
cout << "\nEnter Book ID to borrow : ";
cin >> borrow_id;
while (file >> book_id >> book_name >> author_name >> no_of_copies >> borrowed_copies) {
    if (book_id == borrow_id) {
        found = 1;
        if (no_of_copies - borrowed_copies == 0) {
            cout << "\nAll copies of this book have been borrowed. Please try again later.";
        }
        else {
            borrowed_copies++;
            temp << book_id << " " << book_name << " " << author_name << " " << no_of_copies << " " << borrowed_copies << endl;
            cout << "\nBook borrowed successfully.";
        }
    }
    else {
        temp << book_id << " " << book_name << " " << author_name << " " << no_of_copies << " " << borrowed_copies << endl;
    }
}
if (found == 0) {
    cout << "\nBook not found!!!";
}
file.close();
temp.close();
remove("books.txt");
rename("temp.txt", "books.txt");
}
// Function to display all available books in the library
void Library::available_books() {
    fstream file;
    file.open("books.txt", ios::in);

    if (!file) {
        cout << "\nError in opening file!!!";
        return;
    }

    cout << "\n-------------------------------------------------------------\n";
    cout << "Book ID \t Book Name \t\t Author Name \t Available Copies\n";
    cout << "-------------------------------------------------------------\n";
    while (file >> book_id >> book_name >> author_name >> no_of_copies >> borrowed_copies) {
        if (borrowed_copies < no_of_copies) {
            cout << book_id << "\t\t " << book_name << "\t\t " << author_name << "\t\t " << no_of_copies - borrowed_copies << endl;
        }
    }
    file.close();
}

// Function to return a book
void Library::return_book() {
fstream file, temp;
file.open("books.txt", ios::in);
temp.open("temp.txt", ios::out);
if (!file) {
    cout << "\nError in opening file!!!";
    return;
}
string return_id;
int found = 0;
cout << "\nEnter Book ID to return : ";
cin >> return_id;
while (file >> book_id >> book_name >> author_name >> no_of_copies >> borrowed_copies) {
    if (book_id == return_id) {
        found = 1;
        if (borrowed_copies == 0) {
            cout << "\nThis book has not been borrowed.";
        }
        else {
            borrowed_copies--;
            temp << book_id << " " << book_name << " " << author_name << " " << no_of_copies << " " << borrowed_copies << endl;
            cout << "\nBook returned successfully.";
        }
    }
    else {
        temp << book_id << " " << book_name << " " << author_name << " " << no_of_copies << " " << borrowed_copies << endl;
    }
}
if (found == 0) {
    cout << "\nBook not found!!!";
}
file.close();
temp.close();
remove("books.txt");
rename("temp.txt", "books.txt");
}


void exit_message() {
    cout << "\nThank you for using the library system. Goodbye!\n";
     
}



int main() {
Library l;
int choice;
do {
    l.control_panel();

    cout << "\n\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        l.display_books();
        break;
    case 2:
        l.search_book();
        break;
    case 3:
        l.donate_book();
        break;
    case 4:
        l.borrow_book();
        break;
    case 5:
        l.return_book();
        break;
    case 6:
        l.available_books();
        break;
    case 7:
        exit_message();
        MessageBox(NULL, "Thank you for using our program!", "Exit Message", MB_OK | MB_ICONINFORMATION);
        
        exit(0);
    default:
        cout << "\nInvalid choice!!!";
    }
    cout << "\n\n";
    system("pause");
} while (choice != 7);

return 0;
}
