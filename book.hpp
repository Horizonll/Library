/**
 * @file book.hpp
 * 定义了Book类，用于表示图书信息，并继承自Base类。
 */

#define FILESYSTEM_BOOK "./data/book/"
#include "base.hpp"

/**
 * Book类用于存储和操作图书信息。
 * 包括图书的标题、作者、分类、关键词、简介、借阅次数和借阅状态。
 * 提供了图书信息的增加、保存、删除和编辑功能。
 */
class Book : public Base
{
public:
    // 图书属性
    string title;            ///< 图书标题
    string author;           ///< 作者
    string category;         ///< 分类
    string keywords;         ///< 关键词
    string summary;          ///< 简介
    int borrowTimes = 0;     ///< 借阅次数
    bool isBorrowed = false; ///< 借阅状态

    /**
     * 构造函数，用于创建一个新的Book对象。
     * @param Title 图书标题，默认为空字符串。
     * @param Author 作者，默认为空字符串。
     * @param Category 分类，默认为空字符串。
     * @param Keywords 关键词，默认为空字符串。
     * @param Summary 简介，默认为空字符串。
     */
    Book(string Title = "", string Author = "", string Category = "", string Keywords = "", string Summary = "") : title(Title), author(Author), category(Category), keywords(Keywords), summary(Summary) {}

    /**
     * 拷贝构造函数，用于创建一个新的Book对象，复制已有的Book对象。
     * @param book 已有的Book对象。
     */
    Book(const Book &book) : title(book.title), author(book.author), category(book.category), keywords(book.keywords), summary(book.summary), borrowTimes(book.borrowTimes), isBorrowed(book.isBorrowed) {}

    /**
     * 析构函数。
     */
    ~Book() {}

    /**
     * 添加图书信息到文件系统。
     * @return 成功返回1，文件已存在返回0，失败返回-1。
     */
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

    /**
     * 保存图书信息到文件系统。
     */
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

    /**
     * 从文件系统中删除图书信息。
     * @return 成功返回1，失败返回-1。
     */
    int Delete() const override
    {
        string filePath = FILESYSTEM_BOOK + utf8_to_gbk(this->title) + ".txt";
        if (remove(filePath.c_str()) == 0)
            return 1;
        else
            return -1;
    }

    /**
     * 编辑已有的图书信息。
     * @return 成功返回1，失败返回-1。
     */
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

/**
 * 重载输出操作符，用于打印图书信息。
 * @param os 输出流对象。
 * @param book 要输出的Book对象。
 * @return 输出流对象。
 */
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