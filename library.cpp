#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class Book {
    private:
    int id;
    string title;
    string author;
    bool isBorrowed;
public:
void setBookDetails(int id, string title, string author, bool status){
this->id=id;
this->title=title;
this->author=author;
this->isBorrowed=status;
}
void display(){
    cout<<"ID: "<<id<<", Title: "<<title<<", Author: "<<author<<", Status: "<<(isBorrowed ? "Borrowed" : "Available")<<endl;
}
void borrowBook(){
    isBorrowed=true;
}
void returnBook(){
    isBorrowed=false;
}
bool isAvailable(){
    return isBorrowed;
}
int getId(){
    return id;
}
string getTitle(){
    return title;
}

string getAuthor(){
    return author;
}
string getSaveFormat(int id, string title, string author, bool status){
    string concatinatedVersion=to_string(id)+","+title+","+author+","+to_string(status);
    return concatinatedVersion;
}
};


class Library {
    private:
    Book bookCatalog[50];
    int bookCount;
    string bookFileName;
public:
Library(string filename){
bookFileName=filename;
loadBooksFromFile();
}
    void loadBooksFromFile() {
        ifstream file(bookFileName);
        string line;
        bookCount = 0;
        while (getline(file, line)) {
           int pos1 =line.find(',');
           int pos2 =line.find(',',pos1+1);
           int pos3 =line.find(',',pos2+1);

           bookCatalog[bookCount].setBookDetails(stoi(line.substr(0,pos1)),
           line.substr(pos1+1,pos2-pos1-1),//substr(index,length) unlike java substring(index,index)
              line.substr(pos2+1,pos3-pos2-1),
              stoi(line.substr(pos3+1))
            );
              bookCount++;
        }
        file.close();
    }

    void saveBooksToFile(){
        ofstream file(bookFileName);
        for(int i=0;i<bookCount;i++){
            file<<bookCatalog[i].getSaveFormat(
                bookCatalog[i].getId(),
                bookCatalog[i].getTitle(),
                bookCatalog[i].getAuthor(),
                bookCatalog[i].isAvailable()
            )<<endl;
        }
        file.close();
    }
    void listBooks() {
       for(int i=0;i<bookCount;i++){
        bookCatalog[i].display();
       }
    }

    void borrowBook(int bookId) {
        int isFound=0;
        for(int i=0;i<bookCount;i++){
            if(bookCatalog[i].getId()==bookId){
                isFound=1;
                if(!bookCatalog[i].isAvailable()){
                    bookCatalog[i].borrowBook();
                    cout<<"Book borrowed successfully: "<<bookCatalog[i].getTitle()<<endl;
                }else{
                    cout<<"Error: Book is already borrowed."<<endl;
                }
                return;
            }
        }
        if (isFound==0)
        {
            cout<<"Error: Book not found."<<endl;
        }
        
    }

    void returnBook(int bookId) {
        for(int i=0;i<bookCount;i++){
            if(bookCatalog[i].getId()==bookId){
                if(bookCatalog[i].isAvailable()){
                    bookCatalog[i].returnBook();
                    cout<<"Book returned successfully: "<<bookCatalog[i].getTitle()<<endl;
                }else{
                    cout<<"Error: Book was not borrowed."<<endl;
                }
                return;
            }else{
                cout<<"Error: Book not found."<<endl;
            }
        }
    }
};
int main(){
    Library library("books.txt");
    Book book;
    bool loop=true;
    while (loop)
    {
         int choice;
         cout<<"---------------------------------"<<endl;
         cout << "Welcome to the Library Management System" << endl;
         cout << "please select an option:" << endl;
         cout << "1. List all books" << endl;
         cout << "2. Borrow a book" << endl;
         cout << "3. Return a book" << endl;
         cout << "4. Save and Exit" << endl;
         cout<<"---------------------------------"<<endl;
         cin>> choice;
         switch(choice){
             case 1:
            library.listBooks();
            break;
        case 2:
            {
                int bookId;
                cout << "Enter Book ID to borrow: ";
                cin >> bookId;
                library.borrowBook(bookId);
            }
            break;
        case 3:
            {
                int bookId;
                cout << "Enter Book ID to return: ";
                cin >> bookId;
                library.returnBook(bookId);
            }
            break;
        case 4:
            cout << "Saving changes... Goodbye!" << endl;
            library.saveBooksToFile();
            loop=false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
    }
    return 0;
   
}