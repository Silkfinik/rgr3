#include <iostream>
#include <fstream>
#include <set>
#include <string>

class Book{
private:
    int udk;
    std::set<std::string> authors;
    std::string name;
    int year;
public:
    Book(const int& udk, const std::set<std::string>& authors, const std::string& name, const int& year){
        this->udk = udk;
        this->authors = authors;
        this->name = name;
        this->year = year;
    }
    Book(){
        this->udk = 0;
        this->name = "";
        this->year = 0;
    }
    std::string get_name() const{
        return name;
    }
    void set_udk(const int& n){
        udk = n;
    }
    void set_authors(std::string str){
        while(str.find(',') != std::string::npos){
            authors.insert(str.substr(0, str.find(',')));
            str = str.substr(str.find(',') + 1);
        }
        authors.insert(str);
    }
    void set_name(const std::string& str){
        name = str;
    }
    void set_year(const int& n){
        year = n;
    }
};

struct comp_by_name {
    bool operator()(const Book& a, const Book& b) const {
        return a.get_name() < b.get_name();
    }
};

void file_read(std::set<Book, comp_by_name>& books){
    std::ifstream in("books.txt");
    Book temp;
    if(in.is_open()){
        std::string str;
        while(std::getline(in, str)){
            temp.set_udk(std::stoi(str.substr(0, str.find(';'))));
            str = str.substr(str.find(';') + 1);
            temp.set_authors(str.substr(0, str.find(';')));
            str = str.substr(str.find(';') + 1);
            temp.set_name(str.substr(0, str.find(';')));
            temp.set_year(std::stoi(str.substr(str.rfind(';') + 1)));
            books.insert(temp);
        }
    }
    in.close();
}

void add_book(std::set<Book, comp_by_name>& books, ){

}

int main(){
    std::set<Book, comp_by_name> books;
    file_read(books);
    std::cout << " ";
}