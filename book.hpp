#define FILESYSTEM_BOOK "./data/book/"
#include "base.hpp"

class Book : public Base
{
public:
    string title;
    string author;
    string category;
    string keywords;
    string summary;
    int borrowTimes = 0;
    bool isBorrowed = false;

    Book(string Title = "", string Author = "", string Category = "", string Keywords = "", string Summary = "") : title(Title), author(Author), category(Category), keywords(Keywords), summary(Summary) {}
    Book(const Book &book) : title(book.title), author(book.author), category(book.category), keywords(book.keywords), summary(book.summary), borrowTimes(book.borrowTimes), isBorrowed(book.isBorrowed) {}
    ~Book() {}

    int Add() const override
    {
        string filePath = FILESYSTEM_BOOK + utf8_to_gbk(this->title) + ".txt";
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

    void Save() const override
    {
        string filePath = FILESYSTEM_BOOK + utf8_to_gbk(this->title) + ".txt";
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

    int Delete() const override
    {
        string filePath = FILESYSTEM_BOOK + utf8_to_gbk(this->title) + ".txt";
        if (remove(filePath.c_str()) == 0)
            return 1;
        else
            return -1;
    }

    int Edit() const override
    {
        ofstream file(FILESYSTEM_BOOK + utf8_to_gbk(this->title) + ".txt");
        if (!file)
            return -1;
        else
        {
            this->Save();
            file.close();
            return 1;
        }
    }

    friend ostream &operator<<(ostream &, const Book &);
};

ostream &operator<<(ostream &os, const Book &book)
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