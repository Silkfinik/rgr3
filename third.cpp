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
    Book(const int& udk, const std::string& authors, const std::string& name, const int& year){
        this->udk = udk;
        set_authors(authors);
        this->name = name;
        this->year = year;
    }
    Book(){
        this->udk = 0;
        this->name = "";
        this->year = 0;
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
    int get_udk() const{
        return udk;
    }
    std::string get_authors() const{
        std::string temp;
        for (auto& i : authors){
            temp += i + ',';
        }
        temp.erase(temp.end() - 1);
        return temp;
    }
    std::string get_name() const{
        return name;
    }
    int get_year() const{
        return year;
    }
};

struct comp_by_name {
    bool operator()(const Book& a, const Book& b) const {
        return a.get_name() < b.get_name();
    }
};

void file_read(std::multiset<Book, comp_by_name>& books){
    std::ifstream in("books.txt");
    if(in.is_open()){
        std::string str;
        while(std::getline(in, str)){
            Book temp;
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

void add_book(std::multiset<Book, comp_by_name>& books, const int& udk, const std::string& authors,
              const std::string& name, const int& year){
    books.insert(Book(udk, authors, name, year));
}

void delete_book(std::multiset<Book, comp_by_name>& books, const int& udk, const std::string& authors,
              const std::string& name, const int& year){
    for (auto it = books.begin(); it != books.end(); it++) {
        if (it->get_udk() == udk && it->get_name() == name && it->get_authors() == authors && it->get_year() == year) {
            books.erase(it);
            return;
        }
    }
}

std::multiset<Book, comp_by_name> search_by_name(const std::multiset<Book, comp_by_name>& books, std::string name){
    std::multiset<Book, comp_by_name> temp;
    for (auto& i : books){
        if (i.get_name().find(name) != std::string::npos){
            temp.insert(Book(i.get_udk(), i.get_authors(), i.get_name(), i.get_year()));
        }
    }
    return temp;
}

std::multiset<Book, comp_by_name> search_by_author(const std::multiset<Book, comp_by_name>& books, std::string author){
    std::multiset<Book, comp_by_name> temp;
    for (auto& i : books){
        if (i.get_authors().find(author) != std::string::npos){
            temp.insert(Book(i.get_udk(), i.get_authors(), i.get_name(), i.get_year()));
        }
    }
    return temp;
}

void add_delete_author_by_udk(std::multiset<Book, comp_by_name>& books, const int& udk,
                              const std::string& author, const char& ch) {
    for (auto &i: books) {
        if (i.get_udk() == udk) {
            if (ch == 'a') {
                std::string temp = i.get_authors() + ',' + author;
                Book temp_book(i.get_udk(), temp, i.get_name(), i.get_year());
                for (auto it = books.begin(); it != books.end(); it++) {
                    if (it->get_udk() == udk) {
                        books.erase(it);
                        books.insert(temp_book);
                        return;
                    }
                }
            } else {
                std::string temp = i.get_authors();
                temp = temp.erase(temp.find(author) - 1, temp.find(author) + author.size());
                Book temp_book(i.get_udk(), temp, i.get_name(), i.get_year());
                for (auto it = books.begin(); it != books.end(); it++) {
                    if (it->get_udk() == udk) {
                        books.erase(it);
                        books.insert(temp_book);
                        return;
                    }
                }
            }
        }
    }
}

void print_books(const std::multiset<Book, comp_by_name>& books){
    std::cout << " -----------------------------\n";
    std::cout << "| Udk | Authors | Name | Year |" << std::endl;
    std::cout << " -----------------------------\n";
    for (auto& i : books){
        std::cout << i.get_udk() << " | " << i.get_authors() << " | " << "\"" <<
        i.get_name() << "\" | " << i.get_year() << std::endl;
    }
    std::cout << std::endl;
}

int main(){
    std::multiset<Book, comp_by_name> books;
    file_read(books);
    std::cout << "All books: " << std::endl;
    print_books(books);
    delete_book(books, 2398456, "Glek Q.W.,Sasun A.B.", "a", 1950);
    std::cout << "After deleting: " << std::endl;
    print_books(books);
    std::string temp = "Ko";
    std::multiset<Book, comp_by_name> name = search_by_name(books, temp);
    std::cout << "Search by name: " << std::endl;
    print_books(name);
    std::string author = "Glek Q.W.";
    std::multiset<Book, comp_by_name> authors = search_by_author(books, author);
    std::cout << "Search by author: " << std::endl;
    print_books(authors);
    add_delete_author_by_udk(books, 1, "kjsdfhkjsdfh", 'a');
    std::cout << "After adding: " << std::endl;
    print_books(books);
    add_delete_author_by_udk(books, 1, "kjsdfhkjsdfh", 'd');
    std::cout << "After deleting: " << std::endl;
    print_books(books);
}