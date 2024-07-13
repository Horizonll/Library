/**
 * @file manager.hpp
 * @brief 管理图书和用户的主要功能类
 * Manager 类继承自 BookManager 和 UserManager，提供了管理图书和用户的高级功能，
 * 包括借书、还书以及获取当前日期时间。
 */

#include "bookmanager.hpp"
#include "usermanager.hpp"

class Manager : public BookManager, public UserManager
{
public:
    /**
     * @brief 获取当前日期和时间的字符串表示形式
     * @return 当前日期和时间的字符串，格式为 YYYY-MM-DD HH:MM:SS
     */
    string getCurrentDateTime() const
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
        return buffer;
    }

    /**
     * 根据用户名和书名进行借书操作。如果书已被借出或用户/书不存在，则返回错误代码。
     * @brief 借书操作
     * @param userName 借书用户的用户名
     * @param bookName 被借的书名
     * @return 操作结果代码：1 成功，0 书不存在，-1 书已被借出，-2 用户不存在
     */
    int borrowBook(const string &userName, const string &bookName) const
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
        user.Save();
        book.isBorrowed = true;
        book.borrowTimes++;
        book.Save();
        return 1;
    }

    /**
     * 根据用户名和书名进行还书操作。如果书未被当前用户借出或用户/书不存在，则返回错误代码。
     * @brief 还书操作
     * @param userName 还书用户的用户名
     * @param bookName 被还的书名
     * @return 操作结果代码：1 成功，0 书不存在，-1 书未被当前用户借出，-2 用户不存在
     */
    int returnBook(const string &userName, const string &bookName) const
    {
        Book book = getBook(bookName);
        if (book.title == "")
            return 0;
        User user = getUser(userName);
        if (user.name == "")
            return -2;
        bool found = false;
        for (auto &record : user.borrowRecords)
        {
            if (record.bookName == bookName && !record.isReturned)
            {
                record.returnTime = getCurrentDateTime();
                record.isReturned = true;
                user.Save();
                book.isBorrowed = false;
                book.Save();
                return 1;
            }
        }
        return -1;
    }
};