#include <fstream>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <iconv.h>

using namespace std;

string getCurrentDateTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return buffer;
}

string utf8_to_gbk(const string &utf8_str)
{
    iconv_t cd = iconv_open("GBK", "UTF-8");
    if (cd == (iconv_t)-1)
        return "";
    size_t in_bytes_left = utf8_str.size();
    size_t out_bytes_left = in_bytes_left * 2;
    char *in_buf = const_cast<char *>(utf8_str.c_str());
    char out_buf[out_bytes_left];
    char *out_buf_start = out_buf;
    size_t ret = iconv(cd, &in_buf, &in_bytes_left, &out_buf_start, &out_bytes_left);
    if (ret == (size_t)-1)
    {
        iconv_close(cd);
        return "";
    }
    *out_buf_start = '\0';
    iconv_close(cd);
    return string(out_buf);
}

string gbk_to_utf8(const string &gbk_str)
{
    iconv_t cd = iconv_open("UTF-8", "GBK");
    if (cd == (iconv_t)-1)
        return "";
    size_t in_bytes_left = gbk_str.size();
    size_t out_bytes_left = in_bytes_left * 2;
    char *in_buf = const_cast<char *>(gbk_str.c_str());
    char out_buf[out_bytes_left];
    char *out_buf_start = out_buf;
    size_t ret = iconv(cd, &in_buf, &in_bytes_left, &out_buf_start, &out_bytes_left);
    if (ret == (size_t)-1)
    {
        iconv_close(cd);
        return "";
    }
    *out_buf_start = '\0';
    iconv_close(cd);
    return string(out_buf);
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

    Book(string Title = "", string Author = "", string Category = "", string Keywords = "", string Summary = "", int BorrowTimes = 0, bool IsBorrowed = false)
        : title(Title), author(Author), category(Category), keywords(Keywords), summary(Summary), borrowTimes(BorrowTimes), isBorrowed(IsBorrowed) {}
    Book(const Book &book)
        : title(book.title), author(book.author), category(book.category), keywords(book.keywords), summary(book.summary), borrowTimes(book.borrowTimes), isBorrowed(book.isBorrowed) {}
    ~Book() {}

    int addBook()
    {
        string filePath = "./data/book/" + utf8_to_gbk(this->title) + ".txt";
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
        string filePath = "./data/book/" + utf8_to_gbk(this->title) + ".txt";
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
        string filePath = "./data/book/" + utf8_to_gbk(this->title) + ".txt";
        if (remove(filePath.c_str()) == 0)
            return 1;
        else
            return -1;
    }

    int editBook()
    {
        ofstream file("./data/book/" + utf8_to_gbk(this->title) + ".txt");
        if (!file)
            return -1;
        else
        {
            this->saveBook();
            file.close();
            return 1;
        }
    }
    friend ostream &operator<<(ostream &, Book &);
};

ostream &operator<<(ostream &os, Book &book)
{
    os << "书名：" << book.title << endl;
    os << "作者：" << book.author << endl;
    os << "分类：" << book.category << endl;
    os << "关键词：" << book.keywords << endl;
    os << "简介：" << book.summary << endl;
    if (book.isBorrowed)
        os << "借出状态：已借出" << endl;
    else
        os << "借出状态：未借出" << endl;
    os << "借出次数：" << book.borrowTimes << endl;
    return os;
}

class User
{
public:
    string name;
    vector<Record> borrowRecords;
    int borrowTimes = 0;

    User(string Name = "") : name(Name) {}
    User(const User &user)
        : name(user.name), borrowRecords(user.borrowRecords), borrowTimes(user.borrowTimes) {}
    ~User() {}

    void saveRecords()
    {
        string filePath = "./data/user/" + utf8_to_gbk(this->name) + ".txt";
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
        string filePath = "./data/user/" + utf8_to_gbk(this->name) + ".txt";
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

    int deleteUser()
    {
        string filePath = "./data/user/" + utf8_to_gbk(this->name) + ".txt";
        if (remove(filePath.c_str()) == 0)
            return 1;
        else
            return -1;
    }

    int editUser()
    {
        ofstream file("./data/user/" + utf8_to_gbk(this->name) + ".txt");
        if (!file)
            return -1;
        else
        {
            this->saveRecords();
            file.close();
            return 1;
        }
    }
    friend ostream &operator<<(ostream &, User &);
};

ostream &operator<<(ostream &os, User &user)
{
    os << "借阅次数：" << user.borrowTimes << endl;
    os << endl;
    os << "借阅记录：" << endl;
    os << endl;
    for (auto record : user.borrowRecords)
    {
        os << "书名：" << record.bookName << endl;
        os << "借书时间：" << record.borrowTime << endl;
        if (record.isReturned)
            os << "还书时间：" << record.returnTime << endl;
        else
            os << "还书时间：未还" << endl;
        os << endl;
    }
    return os;
}

class BookManager
{
public:
    Book getBook(string title)
    {
        string filePath = "./data/book/" + utf8_to_gbk(title) + ".txt";
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
            filePath = utf8_to_gbk(filePath);
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

    vector<Book> tenHotBooks()
    {
        vector<Book> results;
        string directory = "./data/book/";
        for (const auto &entry : filesystem::directory_iterator(directory))
        {
            string filePath = entry.path().string();
            filePath = utf8_to_gbk(filePath);
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
                if (book.borrowTimes > 0)
                    results.push_back(book);
            }
        }
        sort(results.begin(), results.end(), [](Book a, Book b)
             { return a.borrowTimes > b.borrowTimes; });
        if (results.size() > 10)
            results.resize(10);
        return results;
    }
};

class UserManager
{
public:
    User getUser(string name)
    {
        string filePath = "./data/user/" + name + ".txt";
        filePath = utf8_to_gbk(filePath);
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
            filePath = utf8_to_gbk(filePath);
            ifstream file(filePath);
            if (file)
            {
                User user;
                user.name = gbk_to_utf8(filePath.substr(12, filePath.size() - 16));
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

    vector<User> tenActiveUsers()
    {
        vector<User> results;
        string directory = "./data/user/";
        for (const auto &entry : filesystem::directory_iterator(directory))
        {
            string filePath = entry.path().string();
            filePath = utf8_to_gbk(filePath);
            ifstream file(filePath);
            if (file)
            {
                User user;
                user.name = gbk_to_utf8(filePath.substr(12, filePath.size() - 16));
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
                if (user.borrowTimes > 0)
                    results.push_back(user);
            }
        }
        sort(results.begin(), results.end(), [](User a, User b)
             { return a.borrowTimes > b.borrowTimes; });
        if (results.size() > 10)
            results.resize(10);
        return results;
    }
};

class Manager : public BookManager, public UserManager
{
public:
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
};