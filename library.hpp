/**
 * @file library.hpp
 * @brief 提供Library类的定义，该类继承自GUI类，用于实现图书馆系统的核心功能。
 * 该文件包含Library类的定义，该类扩展了GUI类，添加了检查和创建必要文件系统目录的功能，并且定义了一个枚举类型Choice，用于表示用户在图书馆系统中可以进行的操作。
 */

#include "gui.hpp"

/**
 * @enum Choice
 * @brief 定义用户在图书馆系统中可以选择进行的操作。
 * 该枚举包含了用户可以在图书馆系统中执行的所有操作，如添加、删除、搜索和编辑图书和用户，借阅和归还图书，查看借阅记录，查看热门图书和活跃用户，删除所有图书和用户，以及退出系统。
 */
enum Choice
{
    AddBook = 1,
    DeleteBook,
    SearchBook,
    EditBook,
    AddUser,
    DeleteUser,
    SearchUser,
    EditUser,
    BorrowBook,
    ReturnBook,
    BorrowRecord,
    TenHotBooks,
    TenActiveUsers,
    DeleteAllBooks,
    DeleteAllUsers,
    Exit
};

/**
 * @class Library
 * @brief 图书馆系统的核心类，继承自GUI类。
 * Library类继承自GUI类，提供了检查和创建图书馆系统所需的文件系统目录的功能。该类是图书馆系统的核心，通过继承GUI类，它也间接提供了用户界面和与用户交互的功能。
 */
class Library : public GUI
{
public:
    /**
     * @brief 检查并创建图书和用户信息存储所需的目录。
     * 该方法检查图书和用户信息存储所需的目录是否存在，如果不存在，则创建这些目录。这是图书馆系统启动时进行的初始化步骤之一。
     */
    void CheckDirectory() const
    {
        if (!filesystem::exists(FILESYSTEM_BOOK))
            filesystem::create_directories(FILESYSTEM_BOOK);
        if (!filesystem::exists(FILESYSTEM_USER))
            filesystem::create_directories(FILESYSTEM_USER);
    }
};