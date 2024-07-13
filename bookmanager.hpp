/**
 * @file bookmanager.hpp
 * @brief 管理书籍信息的类，包括获取书籍、搜索书籍、获取热门书籍和删除所有书籍的功能。
 */

#include "book.hpp"

/**
 * @class BookManager
 * @brief 用于管理书籍信息。
 * 提供了获取单本书籍信息、根据关键字搜索书籍、获取借阅次数最多的十本书籍以及删除所有书籍信息的功能。
 */
class BookManager
{
public:
    /**
     * @brief 根据书名获取书籍信息。
     * @param title 书籍的标题。
     * @return 如果找到书籍，则返回书籍对象；否则，返回一个空的书籍对象。
     */
    Book getBook(const string &title) const
    {
        string filePath = FILESYSTEM_BOOK + utf8_to_gbk(title) + ".txt";
        if (!ifstream(filePath))
        {
            return Book();
        }
        else
        {
            ifstream file(filePath);
            if (!file)
            {
                return Book();
            }
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

    /**
     * @brief 根据关键字搜索书籍。
     * @param keyword 搜索书籍时使用的关键字。
     * @return 包含所有匹配关键字的书籍对象的向量。
     */
    vector<Book> searchBook(const string &keyword) const
    {
        vector<Book> results;
        for (const auto &entry : filesystem::directory_iterator(FILESYSTEM_BOOK))
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
                {
                    results.push_back(book);
                }
            }
        }
        return results;
    }

    /**
     * @brief 获取借阅次数最多的十本书籍。
     * @return 包含借阅次数最多的十本书籍的向量。
     */
    vector<Book> tenHotBooks() const
    {
        vector<Book> results;
        for (const auto &entry : filesystem::directory_iterator(FILESYSTEM_BOOK))
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
                {
                    results.push_back(book);
                }
            }
        }
        sort(results.begin(), results.end(), [](Book a, Book b)
             { return a.borrowTimes > b.borrowTimes; });
        if (results.size() > 10)
        {
            results.resize(10);
        }
        return results;
    }

    /**
     * @brief 删除所有书籍信息。
     * @return 总是返回1，表示操作完成。
     */
    int deleteAllBooks() const
    {
        for (const auto &entry : filesystem::directory_iterator(FILESYSTEM_BOOK))
        {
            string filePath = entry.path().string();
            filePath = utf8_to_gbk(filePath);
            remove(filePath.c_str());
        }
        return 1;
    }
};