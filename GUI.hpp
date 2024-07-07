#include "class.hpp"
#include <conio.h>
#include <iostream>

class GUI
{
public:
    void ShowMenu()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                           图书管理系统" << endl;
        cout << "                        -----------------" << endl;
        cout << "                        1. 添加书籍" << endl;
        cout << "                        2. 删除书籍" << endl;
        cout << "                        3. 查找书籍" << endl;
        cout << "                        4. 编辑书籍" << endl;
        cout << "                        5. 添加用户" << endl;
        cout << "                        6. 删除用户" << endl;
        cout << "                        7. 查找用户" << endl;
        cout << "                        8. 编辑用户" << endl;
        cout << "                        9. 借书" << endl;
        cout << "                        10. 还书" << endl;
        cout << "                        11. 查看借阅记录" << endl;
        cout << "                        12. 十大热门书籍" << endl;
        cout << "                        13. 十大活跃用户" << endl;
        cout << "                        14. 退出" << endl;
    }

    void DisplayBook(Book book)
    {
        cout << "                        书名：" << book.title << endl;
        cout << "                        作者：" << book.author << endl;
        cout << "                        分类：" << book.category << endl;
        cout << "                        关键词：" << book.keywords << endl;
        cout << "                        简介：" << book.summary << endl;
        if (book.isBorrowed == 1)
        {
            cout << "                        借出状态：已借出" << endl;
        }
        else
        {
            cout << "                        借出状态：未借出" << endl;
        }
        cout << "                        借阅次数：" << book.borrowTimes << endl;
    }

    string RemoveBlank(string str)
    {
        auto start = str.find_first_not_of(" \t\n\r\f\v");
        if (start == string::npos)
            return "";
        auto end = str.find_last_not_of(" \t\n\r\f\v");
        return str.substr(start, end - start + 1);
    }

    void AddBook()
    {
        system("cls");
        Book book;
        cout << endl;
        cout << endl;
        cout << "                        添加书籍" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入书名：";
        getline(cin, book.title);
        book.title = RemoveBlank(book.title);
        if (book.title.empty())
        {
            cout << endl;
            cout << "                        书名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        else if (getBook(book.title).title == book.title)
        {
            cout << "                        书籍已存在" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        cout << "                        请输入作者：";
        getline(cin, book.author);
        book.author = RemoveBlank(book.author);
        cout << "                        请输入分类：";
        getline(cin, book.category);
        book.category = RemoveBlank(book.category);
        cout << "                        请输入关键词：";
        getline(cin, book.keywords);
        book.keywords = RemoveBlank(book.keywords);
        cout << "                        请输入简介：";
        getline(cin, book.summary);
        book.summary = RemoveBlank(book.summary);
        cout << endl;
        int result = book.addBook();
        switch (result)
        {
        case 0:
            cout << "                        书籍已存在" << endl;
            break;
        case -1:
            cout << "                        保存失败" << endl;
            break;
        case 1:
            cout << "                        保存成功" << endl;
            break;
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void DeleteBook()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        删除书籍" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入书名：";
        string title;
        getline(cin, title);
        title = RemoveBlank(title);
        cout << endl;
        if (title.empty())
        {
            cout << "                        书名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        if (getBook(title).title.empty())
        {
            cout << "                        书籍不存在" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        Book book(title);
        int result = book.deleteBook();
        switch (result)
        {
        case -1:
            cout << "                        删除失败" << endl;
            break;
        case 1:
            cout << "                        删除成功" << endl;
            break;
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void SearchBook()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        查找书籍" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入搜索词（回车显示所有书籍）：";
        string title;
        getline(cin, title);
        title = RemoveBlank(title);
        cout << endl;
        cout << "                        查询结果" << endl;
        cout << endl;
        vector<Book> books = searchBook(title);
        int result = books.size() == 0 ? 0 : 1;
        switch (result)
        {
        case 0:
            cout << "                        书籍不存在" << endl;
            break;
        case 1:
            for (int i = 0; i < books.size(); i++)
            {
                cout << "                        书籍" << i + 1 << endl;
                DisplayBook(books[i]);
                cout << endl;
            }
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void EditBook()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        编辑书籍" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入书名：";
        string title;
        getline(cin, title);
        title = RemoveBlank(title);
        cout << endl;
        if (title.empty())
        {
            cout << "                        书名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        Book oldBook = getBook(title);
        int result = oldBook.title.empty() ? 0 : 1;
        switch (result)
        {
        case 0:
            cout << "                        书籍不存在" << endl;
            break;
        case 1:
            DisplayBook(oldBook);
            Book book;
            cout << endl;
            cout << "                        请输入新书名：";
            getline(cin, book.title);
            book.title = RemoveBlank(book.title);
            if (book.title.empty())
            {
                cout << endl;
                cout << "                        书名不能为空" << endl;
                cout << endl;
                cout << "                        按任意键返回" << endl;
                getch();
                return;
            }
            cout << "                        请输入新作者：";
            getline(cin, book.author);
            book.author = RemoveBlank(book.author);
            cout << "                        请输入新分类：";
            getline(cin, book.category);
            book.category = RemoveBlank(book.category);
            cout << "                        请输入新关键词：";
            getline(cin, book.keywords);
            book.keywords = RemoveBlank(book.keywords);
            cout << "                        请输入新简介：";
            getline(cin, book.summary);
            book.summary = RemoveBlank(book.summary);
            cout << endl;
            oldBook.deleteBook();
            int result = book.editBook();
            switch (result)
            {
            case -1:
                cout << "                        保存失败" << endl;
                break;
            case 1:
                cout << "                        保存成功" << endl;
                break;
            }
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void AddUser()
    {
        system("cls");
        User user;
        cout << endl;
        cout << endl;
        cout << "                        添加用户" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入用户名：";
        getline(cin, user.name);
        user.name = RemoveBlank(user.name);
        cout << endl;
        if (user.name.empty())
        {
            cout << "                        用户名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        int result = user.addUser();
        switch (result)
        {
        case 0:
            cout << "                        用户已存在" << endl;
            break;
        case -1:
            cout << "                        保存失败" << endl;
            break;
        case 1:
            cout << "                        保存成功" << endl;
            break;
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void DeleteUser()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        删除用户" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入用户名：";
        string name;
        getline(cin, name);
        name = RemoveBlank(name);
        cout << endl;
        if (name.empty())
        {
            cout << "                        用户名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        if (getUser(name).name.empty())
        {
            cout << "                        用户不存在" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        User user(name);
        int result = user.deleteUser();
        switch (result)
        {
        case 1:
            cout << "                        删除成功" << endl;
            break;
        case -1:
            cout << "                        删除失败" << endl;
            break;
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void SearchUser()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        查找用户" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入用户名（回车显示所有用户）：";
        string name;
        getline(cin, name);
        cout << endl;
        cout << "                        查询结果" << endl;
        cout << endl;
        vector<User> users = searchUser(name);
        int result = users.size() == 0 ? 0 : 1;
        switch (result)
        {
        case 0:
            cout << "                        用户不存在" << endl;
            break;
        case 1:
            for (int i = 0; i < users.size(); i++)
            {
                cout << "                        用户" << i + 1 << "：" << users[i].name << endl;
                cout << endl;
            }
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void EditUser()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        编辑用户" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入用户名：";
        string oldname;
        getline(cin, oldname);
        oldname = RemoveBlank(oldname);
        cout << endl;
        if (oldname.empty())
        {
            cout << "                        用户名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        User user = getUser(oldname);
        int result = user.name.empty() ? 0 : 1;
        switch (result)
        {
        case 0:
            cout << "                        用户不存在" << endl;
            break;
        case 1:
            cout << "                        请输入新用户名：";
            getline(cin, user.name);
            user.name = RemoveBlank(user.name);
            cout << endl;
            if (user.name.empty())
            {
                cout << "                        用户名不能为空" << endl;
                cout << endl;
                cout << "                        按任意键返回" << endl;
                getch();
                return;
            }
            int result = user.editUser(oldname);
            switch (result)
            {
            case -1:
                cout << "                        保存失败" << endl;
                break;
            case 1:
                cout << "                        保存成功" << endl;
                break;
            }
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void BorrowBook()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        借书" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入书名：";
        string title;
        getline(cin, title);
        title = RemoveBlank(title);
        cout << endl;
        if (title.empty())
        {
            cout << "                        书名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        cout << "                        请输入用户名：";
        string name;
        getline(cin, name);
        name = RemoveBlank(name);
        cout << endl;
        if (name.empty())
        {
            cout << "                        用户名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        int result = borrowBook(name, title);
        switch (result)
        {
        case 0:
            cout << "                        书籍不存在" << endl;
            break;
        case -1:
            cout << "                        书籍已借出" << endl;
            break;
        case -2:
            cout << "                        用户不存在" << endl;
            break;
        case 1:
            cout << "                        借书成功" << endl;
            break;
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void ReturnBook()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        还书" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入书名：";
        string title;
        getline(cin, title);
        title = RemoveBlank(title);
        cout << endl;
        if (title.empty())
        {
            cout << "                        书名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        cout << "                        请输入用户名：";
        string name;
        getline(cin, name);
        name = RemoveBlank(name);
        cout << endl;
        if (name.empty())
        {
            cout << "                        用户名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        int result = returnBook(name, title);
        switch (result)
        {
        case 0:
            cout << "                        书籍不存在" << endl;
            break;
        case -1:
            cout << "                        未借此书籍" << endl;
            break;
        case -2:
            cout << "                        用户不存在" << endl;
            break;
        case 1:
            cout << "                        还书成功" << endl;
            break;
        case -3:
            cout << "                        用户未借过此书" << endl;
            break;
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void BorrowRecord()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        查看借阅记录" << endl;
        cout << endl;
        cout << endl;
        cout << "                        请输入用户名：";
        string name;
        getline(cin, name);
        name = RemoveBlank(name);
        cout << endl;
        if (name.empty())
        {
            cout << "                        用户名不能为空" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        User user = getUser(name);
        int result = user.name.empty() ? 0 : 1;
        switch (result)
        {
        case 0:
            cout << "                        用户不存在" << endl;
            break;
        case 1:
            cout << "                        借阅次数：" << user.borrowTimes << endl;
            cout << endl;
            cout << "                        借阅记录" << endl;
            cout << endl;
            for (auto record : user.borrowRecords)
            {
                cout << "                        书名：" << record.bookName << endl;
                cout << "                        借书时间：" << record.borrowTime << endl;
                if (record.returnTime == "")
                {
                    cout << "                        还书时间：未还" << endl;
                }
                else
                {
                    cout << "                        还书时间：" << record.returnTime << endl;
                }
                cout << endl;
            }
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void TenHotBooks()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        十大热门书籍" << endl;
        cout << endl;
        cout << endl;
        vector<Book> books = tenHotBooks();
        if (books.size() == 0)
        {
            cout << "                        无借阅记录" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        for (int i = 0; i < books.size(); i++)
        {
            cout << "                        书籍" << i + 1 << endl;
            DisplayBook(books[i]);
            cout << endl;
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void TenActiveUsers()
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "                        十大活跃用户" << endl;
        cout << endl;
        cout << endl;
        vector<User> users = tenActiveUsers();
        if (users.size() == 0)
        {
            cout << "                        无借阅记录" << endl;
            cout << endl;
            cout << "                        按任意键返回" << endl;
            getch();
            return;
        }
        for (int i = 0; i < users.size(); i++)
        {
            cout << "                        用户" << i + 1 << "：" << users[i].name << endl;
            cout << "                        借阅次数：" << users[i].borrowTimes << endl;
            cout << endl;
        }
        cout << endl;
        cout << "                        按任意键返回" << endl;
        getch();
    }

    void Exit()
    {
        exit(0);
    }
    void Error()
    {
        cout << "                        无效输入，请重新输入" << endl;
    }
};