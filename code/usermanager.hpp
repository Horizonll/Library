/**
 * @file usermanager.hpp
 * @brief 用户管理类定义文件
 * 提供了对用户信息进行管理的类，包括获取单个用户信息、搜索用户、获取活跃用户列表和删除所有用户等功能。
 */

#include "user.hpp"

/**
 * @class UserManager
 * @brief 用户管理类
 * 用于管理用户信息，包括获取、搜索、列出活跃用户和删除用户等操作。
 */
class UserManager
{
public:
    /**
     * 根据用户名从文件系统中读取用户信息，包括借阅记录等，并返回一个用户对象。
     * @brief 获取单个用户的信息
     * @param name 用户名
     * @return User 用户对象，如果用户不存在则返回空的用户对象
     */
    User getUser(const string &name) const
    {
        string filePath = FILESYSTEM_USER + name + ".txt";
        filePath = utf8_to_gbk(filePath);
        if (!ifstream(filePath))
        {
            return User();
        }
        else
        {
            ifstream file(filePath);
            if (!file)
            {
                return User();
            }
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

    /**
     * 在所有用户中搜索包含指定关键字的用户名，并返回一个包含这些用户的列表。
     * @brief 搜索包含关键字的用户列表
     * @param keyword 搜索关键字
     * @return vector<User> 包含关键字的用户列表
     */
    vector<User> searchUser(const string &keyword) const
    {
        vector<User> results;
        for (const auto &entry : filesystem::directory_iterator(FILESYSTEM_USER))
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
                {
                    results.push_back(user);
                }
            }
        }
        return results;
    }

    /**
     * 根据用户的借阅次数，获取最活跃的用户列表，列表最多包含10个用户。
     * @brief 获取最活跃的用户列表
     * @return vector<User> 最活跃的用户列表，最多10个
     */
    vector<User> tenActiveUsers() const
    {
        vector<User> results;
        for (const auto &entry : filesystem::directory_iterator(FILESYSTEM_USER))
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
                {
                    results.push_back(user);
                }
            }
        }
        sort(results.begin(), results.end(), [](User a, User b)
             { return a.borrowTimes > b.borrowTimes; });
        if (results.size() > 10)
        {
            results.resize(10);
        }
        return results;
    }

    /**
     * 删除文件系统中所有用户的信息。
     * @brief 删除所有用户
     * @return int 操作结果，成功返回1，失败返回0
     */
    int deleteAllUsers() const
    {
        for (const auto &entry : filesystem::directory_iterator(FILESYSTEM_USER))
        {
            string filePath = entry.path().string();
            filePath = utf8_to_gbk(filePath);
            remove(filePath.c_str());
        }
        return 1;
    }
};