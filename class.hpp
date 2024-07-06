#include <fstream>
#include <vector>
#include <filesystem>

using namespace std;

string getCurrentDateTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return buffer;
}

struct Record
{
    string bookName = "";
    string borrowTime = "";
    string returnTime = "";
    bool isReturned = false;
};

class Book
{
public:
    string title;
    string author;
    string category;
    string keywords;
    string summary;
    int borrowTimes;
    bool isBorrowed;

    Book(string title = "", string author = "", string category = "", string keywords = "", string summary = "", string borrowUser = "", bool isBorrowed = false, int borrowTimes = 0)
    {
        this->title = title;
        this->author = author;
        this->category = category;
        this->keywords = keywords;
        this->summary = summary;
        this->isBorrowed = isBorrowed;
        this->borrowTimes = borrowTimes;
    }
    Book(const Book &book)
    {
        this->title = book.title;
        this->author = book.author;
        this->category = book.category;
        this->keywords = book.keywords;
        this->summary = book.summary;
        this->isBorrowed = book.isBorrowed;
        this->borrowTimes = book.borrowTimes;
    }
    ~Book() {}

    int addBook()
    {
        string filePath = "./data/book/" + this->title + ".txt";
        if (ifstream(filePath))
            return 0;
        else
        {
            ofstream file(filePath);
            if (!file)
                return -1;
            else
            {
                file << this->title << endl;
                file << this->author << endl;
                file << this->category << endl;
                file << this->keywords << endl;
                file << this->summary << endl;
                file << this->isBorrowed << endl;
                file << this->borrowTimes << endl;
                file.close();
                return 1;
            }
        }
    }

    void saveBook()
    {
        string filePath = "./data/book/" + this->title + ".txt";
        ofstream file(filePath);
        file << this->title << endl;
        file << this->author << endl;
        file << this->category << endl;
        file << this->keywords << endl;
        file << this->summary << endl;
        file << this->isBorrowed << endl;
        file << this->borrowTimes << endl;
        file.close();
    }

    int deleteBook()
    {
        string filePath = "./data/book/" + this->title + ".txt";
        if (remove(filePath.c_str()) == 0)
            return 1;
        else
            return -1;
    }

    int editBook()
    {
        ofstream file("./data/book/" + this->title + ".txt");
        if (!file)
            return -1;
        else
        {
            this->saveBook();
            file.close();
            return 1;
        }
    }
};

Book getBook(string title)
{
    string filePath = "./data/book/" + title + ".txt";
    if (!ifstream(filePath))
        return Book();
    else
    {
        ifstream file(filePath);
        if (!file)
            return Book();
        else
        {
            Book book;
            getline(file, book.title);
            getline(file, book.author);
            getline(file, book.category);
            getline(file, book.keywords);
            getline(file, book.summary);
            string line;
            getline(file, line);
            book.isBorrowed = (line == "1");
            getline(file, line);
            book.borrowTimes = stoi(line);
            file.close();
            return book;
        }
    }
}

vector<Book> searchBook(string keyword)
{
    vector<Book> results;
    string directory = "./data/book/";
    for (const auto &entry : filesystem::directory_iterator(directory))
    {
        string filePath = entry.path().string();
        ifstream file(filePath);
        if (file)
        {
            Book book;
            getline(file, book.title);
            getline(file, book.author);
            getline(file, book.category);
            getline(file, book.keywords);
            getline(file, book.summary);
            string line;
            getline(file, line);
            book.isBorrowed = (line == "1");
            getline(file, line);
            book.borrowTimes = stoi(line);
            file.close();

            if (book.title.find(keyword) != string::npos ||
                book.author.find(keyword) != string::npos ||
                book.category.find(keyword) != string::npos ||
                book.keywords.find(keyword) != string::npos ||
                book.summary.find(keyword) != string::npos)
                results.push_back(book);
        }
    }
    return results;
}

class User
{
public:
    string name;
    vector<Record> borrowRecords;
    int borrowTimes = 0;

    User(string name = "")
    {
        this->name = name;
    }
    User(const User &user)
    {
        this->name = user.name;
        this->borrowRecords = user.borrowRecords;
        this->borrowTimes = user.borrowTimes;
    }
    ~User() {}

    void saveRecords()
    {
        string filePath = "./data/user/" + this->name + ".txt";
        ofstream file(filePath);
        for (auto record : this->borrowRecords)
        {
            file << record.bookName << endl;
            file << record.borrowTime << endl;
            file << record.returnTime << endl;
            file << record.isReturned << endl;
        }
        file.close();
    }

    int addUser()
    {
        string filePath = "./data/user/" + this->name + ".txt";
        if (ifstream(filePath))
            return 0;
        else
        {
            ofstream file(filePath);
            if (!file)
                return -1;
            else
            {
                file.close();
                return 1;
            }
        }
    }

    int editUser(string oldname)
    {
        string oldfilePath = "./data/user/" + oldname + ".txt";
        string newfilePath = "./data/user/" + this->name + ".txt";
        if (rename(oldfilePath.c_str(), newfilePath.c_str()) != 0)
            return 0;
        else
            return 1;
    }

    int deleteUser()
    {
        string filePath = "./data/user/" + this->name + ".txt";
        if (remove(filePath.c_str()) == 0)
            return 1;
        else
            return -1;
    }
};

User getUser(string name)
{
    string filePath = "./data/user/" + name + ".txt";
    if (!ifstream(filePath))
        return User();
    else
    {
        ifstream file(filePath);
        if (!file)
            return User();
        else
        {
            User user(name);
            string line;
            while (getline(file, line))
            {
                Record record;
                record.bookName = line;
                getline(file, line);
                record.borrowTime = line;
                getline(file, line);
                record.returnTime = line;
                getline(file, line);
                record.isReturned = (line == "1");
                user.borrowRecords.push_back(record);
            }
            user.borrowTimes = user.borrowRecords.size();
            file.close();
            return user;
        }
    }
}

vector<User> searchUser(string keyword)
{
    vector<User> results;
    string directory = "./data/user/";
    for (const auto &entry : filesystem::directory_iterator(directory))
    {
        string filePath = entry.path().string();
        ifstream file(filePath);
        if (file)
        {
            User user;
            user.name = filePath.substr(12, filePath.size() - 16);
            string line;
            while (getline(file, line))
            {
                Record record;
                record.bookName = line;
                getline(file, line);
                record.borrowTime = line;
                getline(file, line);
                record.returnTime = line;
                getline(file, line);
                record.isReturned = (line == "1");
                user.borrowRecords.push_back(record);
            }
            user.borrowTimes = user.borrowRecords.size();
            file.close();

            if (user.name.find(keyword) != string::npos)
                results.push_back(user);
        }
    }
    return results;
}

int borrowBook(string userName, string bookName)
{
    Book book = getBook(bookName);
    if (book.title == "")
        return 0;
    User user = getUser(userName);
    if (user.name == "")
        return -2;
    if (book.isBorrowed)
        return -1;
    Record record;
    record.bookName = bookName;
    record.borrowTime = getCurrentDateTime();
    record.isReturned = false;
    user.borrowRecords.push_back(record);
    user.borrowTimes = user.borrowRecords.size();
    user.saveRecords();
    book.isBorrowed = true;
    book.borrowTimes++;
    book.saveBook();
    return 1;
}

int returnBook(string userName, string bookName)
{
    Book book = getBook(bookName);
    if (book.title == "")
        return 0;
    User user = getUser(userName);
    if (user.name == "")
        return -2;
    bool found = false;
    bool isBorrowed = false;
    for (auto &record : user.borrowRecords)
    {
        if (record.bookName == bookName && !record.isReturned)
        {
            record.returnTime = getCurrentDateTime();
            record.isReturned = true;
            found = true;
            isBorrowed = true;
            break;
        }
    }
    if (!found)
        return -1;
    if (!isBorrowed)
        return -3;
    user.saveRecords();
    book.isBorrowed = false;
    book.saveBook();
    return 1;
}