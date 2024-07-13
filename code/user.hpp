/**
 * @file user.hpp
 * @brief 定义User类和Record结构体，用于管理用户信息和借阅记录。
 */

#define FILESYSTEM_USER "./data/user/"
#include "base.hpp"

/**
 * @struct Record
 * @brief 存储单个借阅记录的详细信息。
 */
struct Record
{
    string bookName;   ///< 书名
    string borrowTime; ///< 借书时间
    string returnTime; ///< 还书时间
    bool isReturned;   ///< 是否已还书

    /**
     * @brief 默认构造函数，初始化借阅记录。
     */
    Record() : bookName(""), borrowTime(""), returnTime(""), isReturned(false) {}
};

/**
 * @class User
 * @brief 表示一个用户及其借阅记录。
 * 继承自Base类，用于表示一个用户及其借阅记录。
 */
class User : public Base
{
public:
    string name;                  ///< 用户名
    vector<Record> borrowRecords; ///< 用户的借阅记录列表
    int borrowTimes = 0;          ///< 用户的借阅次数

    /**
     * @brief 构造函数，创建一个新的用户对象。
     * @param Name 用户名
     */
    User(string Name = "") : name(Name) {}

    /**
     * @brief 拷贝构造函数，用另一个User对象初始化此对象。
     * @param user 另一个User对象
     */
    User(const User &user) : name(user.name), borrowRecords(user.borrowRecords), borrowTimes(user.borrowTimes) {}

    /**
     * @brief 析构函数。
     */
    ~User() {}

    /**
     * @brief 添加用户信息到文件系统。
     * @return 成功返回1，如果文件已存在返回0，失败返回-1。
     */
    int Add() const override
    {
        string filePath = FILESYSTEM_USER + utf8_to_gbk(this->name) + ".txt";
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

    /**
     * @brief 保存用户的借阅记录到文件系统。
     */
    void Save() const override
    {
        string filePath = FILESYSTEM_USER + utf8_to_gbk(this->name) + ".txt";
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

    /**
     * @brief 从文件系统中删除用户信息。
     * @return 成功返回1，失败返回-1。
     */
    int Delete() const override
    {
        string filePath = FILESYSTEM_USER + utf8_to_gbk(this->name) + ".txt";
        if (remove(filePath.c_str()) == 0)
            return 1;
        else
            return -1;
    }

    /**
     * @brief 编辑用户信息。
     * @return 成功返回1，失败返回-1。
     */
    int Edit() const override
    {
        ofstream file(FILESYSTEM_USER + utf8_to_gbk(this->name) + ".txt");
        if (!file)
            return -1;
        else
        {
            this->Save();
            file.close();
            return 1;
        }
    }

    friend ostream &operator<<(ostream &, const User &);
};

/**
 * @brief 重载输出操作符，用于打印用户信息和借阅记录。
 * @param os 输出流对象
 * @param user 用户对象
 * @return 输出流对象
 */
ostream &operator<<(ostream &os, const User &user)
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