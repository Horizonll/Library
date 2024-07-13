/**
 * @file main.cpp
 * @brief 图书馆系统的入口点。
 * 该文件包含main函数，是图书馆系统的入口点。它初始化Library类的实例，并进入一个循环，不断显示菜单、获取用户输入，并根据输入执行相应的操作。如果用户输入无效，将显示错误信息并重新显示菜单。
 */

#include "library.hpp"

/**
 * @brief 程序的主入口点。
 * 主函数初始化图书馆系统，设置字符编码为UTF-8，检查必要的目录结构，并进入主循环，等待用户输入。根据用户的选择，执行相应的操作，直到用户选择退出程序。
 * @return 程序退出状态。正常退出时返回0。
 */
int main()
{
    Library library;      // 图书馆系统的实例
    bool error = false;   // 错误标志，用于指示是否需要显示错误信息
    system("chcp 65001"); // 设置控制台字符编码为UTF-8

    while (true) // 主循环
    {
        library.CheckDirectory(); // 检查并创建必要的目录结构
        library.ShowMenu();       // 显示主菜单
        if (error)                // 如果之前的输入无效，显示错误信息
            library.Error();

        string input;        // 用户输入
        int choice;          // 用户选择的操作
        getline(cin, input); // 获取用户输入
        // 验证输入是否为有效数字且在操作范围内
        if (!IsPureNumber(input) ||
            input.empty() ||
            (choice = stoi(input)) > Exit || choice < AddBook)
        {
            error = true; // 设置错误标志
            continue;     // 重新进入循环，显示菜单
        }

        // 根据用户选择执行相应操作
        switch (choice)
        {
        case AddBook:
            library.AddBook();
            break;
        case DeleteBook:
            library.DeleteBook();
            break;
        case SearchBook:
            library.SearchBook();
            break;
        case EditBook:
            library.EditBook();
            break;
        case AddUser:
            library.AddUser();
            break;
        case DeleteUser:
            library.DeleteUser();
            break;
        case SearchUser:
            library.SearchUser();
            break;
        case EditUser:
            library.EditUser();
            break;
        case BorrowBook:
            library.BorrowBook();
            break;
        case ReturnBook:
            library.ReturnBook();
            break;
        case BorrowRecord:
            library.BorrowRecord();
            break;
        case TenHotBooks:
            library.TenHotBooks();
            break;
        case TenActiveUsers:
            library.TenActiveUsers();
            break;
        case DeleteAllBooks:
            library.DeleteAllBooks();
            break;
        case DeleteAllUsers:
            library.DeleteAllUsers();
            break;
        case Exit:
            library.Exit(); // 退出程序
            return 0;       // 正常退出
        }
        error = false; // 重置错误标志
    }
}