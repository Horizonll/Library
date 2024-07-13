/**
 * @file GUI.hpp
 * @brief 图书管理系统的图形用户界面(GUI)类定义文件。
 * 该文件包含GUI类的定义。GUI类继承自Manager类，提供了图书管理系统的用户界面功能，包括显示菜单、添加/删除/查找/编辑图书和用户等操作的界面显示和交互。
 */

#include "manager.hpp"

/**
 * @class GUI GUI.hpp "GUI.hpp"
 * @brief 图书管理系统的图形用户界面(GUI)类。
 * GUI类提供了图书管理系统的所有用户界面功能。它允许用户通过文本菜单进行操作，如添加、删除、查找和编辑图书和用户信息。该类继承自Manager类，使用继承而来的方法来执行用户请求的操作。
 */
class GUI : public Manager
{
public:
    /**
     * @brief 显示主菜单。
     * 该方法清屏并显示图书管理系统的主菜单，包括所有可用的操作选项。
     */
    void ShowMenu() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "              图书管理系统" << endl;
        cout << "---------------------------------------" << endl;
        cout << "1. 添加图书            9. 图书借阅" << endl;
        cout << "2. 删除图书            10. 图书归还" << endl;
        cout << "3. 查找图书            11. 借阅记录" << endl;
        cout << "4. 编辑图书            12. 十大热门图书" << endl;
        cout << "5. 添加用户            13. 十大活跃用户" << endl;
        cout << "6. 删除用户            14. 删除所有图书" << endl;
        cout << "7. 查找用户            15. 删除所有用户" << endl;
        cout << "8. 编辑用户            16. 退出" << endl;
        cout << "---------------------------------------" << endl;
        cout << endl;
        cout << "请选择操作：";
    }

    /**
     * @brief 移除字符串前后的空白字符。
     * @param str 输入的字符串。
     * @return 移除前后空白字符后的字符串。
     */
    string RemoveBlank(const string &str) const
    {
        auto start = str.find_first_not_of(" \t\n\r\f\v");
        if (start == string::npos)
            return "";
        auto end = str.find_last_not_of(" \t\n\r\f\v");
        return str.substr(start, end - start + 1);
    }

    /**
     * @brief 显示单本图书的详细信息。
     * @param book 要显示的图书对象。
     */
    void DisplayBook(const Book &book) const
    {
        cout << book;
    }

    /**
     * @brief 添加新图书的界面和逻辑。
     * 该方法引导用户通过一系列提示输入新图书的详细信息，然后尝试添加图书到系统中。
     */
    void AddBook() const
    {
        system("cls");
        Book book;
        cout << endl;
        cout << endl;
        cout << "添加图书" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入书名：";
        getline(cin, book.title);
        book.title = RemoveBlank(book.title);
        if (book.title.empty())
        {
            cout << endl;
            cout << "书名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        else if (getBook(book.title).title == book.title)
        {
            cout << "图书已存在" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        cout << "请输入作者：";
        getline(cin, book.author);
        book.author = RemoveBlank(book.author);
        cout << "请输入分类：";
        getline(cin, book.category);
        book.category = RemoveBlank(book.category);
        cout << "请输入关键词：";
        getline(cin, book.keywords);
        book.keywords = RemoveBlank(book.keywords);
        cout << "请输入简介：";
        getline(cin, book.summary);
        book.summary = RemoveBlank(book.summary);
        cout << endl;
        int result = book.Add();
        switch (result)
        {
        case 0:
            cout << "图书已存在" << endl;
            break;
        case -1:
            cout << "保存失败" << endl;
            break;
        case 1:
            cout << "保存成功" << endl;
            break;
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 删除图书的界面和逻辑。
     * 该方法提示用户输入要删除的图书名称，然后尝试从系统中删除指定的图书。
     */
    void DeleteBook() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "删除图书" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入书名：";
        string title;
        getline(cin, title);
        title = RemoveBlank(title);
        cout << endl;
        if (title.empty())
        {
            cout << "书名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        if (getBook(title).title.empty())
        {
            cout << "图书不存在" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        Book book(title);
        cout << "确认删除？(y/n)";
        string c;
        getline(cin, c);
        cout << endl;
        if (c != "y")
        {
            cout << "取消删除" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        int result = book.Delete();
        switch (result)
        {
        case -1:
            cout << "删除失败" << endl;
            break;
        case 1:
            cout << "删除成功" << endl;
            break;
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 查找图书的界面和逻辑。
     * 该方法提示用户输入搜索词（书名），然后显示所有匹配的图书信息。
     */
    void SearchBook() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "查找图书" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入搜索词（回车显示所有图书）：";
        string title;
        getline(cin, title);
        title = RemoveBlank(title);
        cout << endl;
        cout << "查询结果" << endl;
        cout << endl;
        vector<Book> books = searchBook(title);
        int result = books.size() == 0 ? 0 : 1;
        switch (result)
        {
        case 0:
            cout << "图书不存在" << endl;
            break;
        case 1:
            for (int i = 0; i < books.size(); i++)
            {
                cout << "图书" << i + 1 << endl;
                DisplayBook(books[i]);
                cout << endl;
            }
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 编辑图书信息的界面和逻辑。
     * 该方法首先提示用户输入要编辑的图书名称，然后允许用户修改图书的详细信息。
     */
    void EditBook() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "编辑图书" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入书名：";
        string title;
        getline(cin, title);
        title = RemoveBlank(title);
        cout << endl;
        if (title.empty())
        {
            cout << "书名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        Book oldBook = getBook(title);
        int result = oldBook.title.empty() ? 0 : 1;
        switch (result)
        {
        case 0:
            cout << "图书不存在" << endl;
            break;
        case 1:
            DisplayBook(oldBook);
            Book book;
            cout << endl;
            cout << "请输入新书名：";
            getline(cin, book.title);
            book.title = RemoveBlank(book.title);
            if (book.title.empty())
            {
                cout << endl;
                cout << "书名不能为空" << endl;
                cout << endl;
                cout << "按任意键返回" << endl;
                getch();
                return;
            }
            cout << "请输入新作者：";
            getline(cin, book.author);
            book.author = RemoveBlank(book.author);
            cout << "请输入新分类：";
            getline(cin, book.category);
            book.category = RemoveBlank(book.category);
            cout << "请输入新关键词：";
            getline(cin, book.keywords);
            book.keywords = RemoveBlank(book.keywords);
            cout << "请输入新简介：";
            getline(cin, book.summary);
            book.summary = RemoveBlank(book.summary);
            cout << endl;
            book.isBorrowed = oldBook.isBorrowed;
            book.borrowTimes = oldBook.borrowTimes;
            oldBook.Delete();
            int result = book.Edit();
            switch (result)
            {
            case -1:
                cout << "保存失败" << endl;
                break;
            case 1:
                cout << "保存成功" << endl;
                break;
            }
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 显示单个用户的详细信息。
     * @param user 要显示的用户对象。
     */
    void DisplayUser(const User &user) const
    {
        cout << user;
    }

    /**
     * @brief 添加新用户的界面和逻辑。
     * 该方法引导用户通过一系列提示输入新用户的详细信息，然后尝试添加用户到系统中。
     */
    void AddUser() const
    {
        system("cls");
        User user;
        cout << endl;
        cout << endl;
        cout << "添加用户" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入用户名：";
        getline(cin, user.name);
        user.name = RemoveBlank(user.name);
        cout << endl;
        if (user.name.empty())
        {
            cout << "用户名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        int result = user.Add();
        switch (result)
        {
        case 0:
            cout << "用户已存在" << endl;
            break;
        case -1:
            cout << "保存失败" << endl;
            break;
        case 1:
            cout << "保存成功" << endl;
            break;
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 删除用户的界面和逻辑。
     * 该方法提示用户输入要删除的用户名，然后尝试从系统中删除指定的用户。
     */
    void DeleteUser() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "删除用户" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入用户名：";
        string name;
        getline(cin, name);
        name = RemoveBlank(name);
        cout << endl;
        if (name.empty())
        {
            cout << "用户名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        if (getUser(name).name.empty())
        {
            cout << "用户不存在" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        User user(name);
        cout << "确认删除？(y/n)";
        string c;
        getline(cin, c);
        cout << endl;
        if (c != "y")
        {
            cout << "取消删除" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        int result = user.Delete();
        switch (result)
        {
        case 1:
            cout << "删除成功" << endl;
            break;
        case -1:
            cout << "删除失败" << endl;
            break;
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 搜索用户。
     * 清屏并提示用户输入用户名，根据输入搜索用户。如果未输入用户名，则显示所有用户。根据搜索结果，显示用户信息或提示用户不存在。
     */
    void SearchUser() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "查找用户" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入用户名（回车显示所有用户）：";
        string name;
        getline(cin, name);
        cout << endl;
        cout << "查询结果" << endl;
        cout << endl;
        vector<User> users = searchUser(name);
        int result = users.size() == 0 ? 0 : 1;
        switch (result)
        {
        case 0:
            cout << "用户不存在" << endl;
            break;
        case 1:
            for (int i = 0; i < users.size(); i++)
            {
                cout << "用户" << i + 1 << "：" << users[i].name << endl;
                cout << endl;
            }
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 编辑用户。
     * 清屏并提示用户输入用户名，然后输入新的用户名进行更新。如果用户存在，则更新用户信息；否则，提示用户不存在。
     */
    void EditUser() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "编辑用户" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入用户名：";
        string oldname;
        getline(cin, oldname);
        oldname = RemoveBlank(oldname);
        cout << endl;
        if (oldname.empty())
        {
            cout << "用户名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        User oldUser = getUser(oldname);
        int result = oldUser.name.empty() ? 0 : 1;
        switch (result)
        {
        case 0:
            cout << "用户不存在" << endl;
            break;
        case 1:
            cout << "请输入新用户名：";
            User user;
            getline(cin, user.name);
            user.name = RemoveBlank(user.name);
            cout << endl;
            if (user.name.empty())
            {
                cout << "用户名不能为空" << endl;
                cout << endl;
                cout << "按任意键返回" << endl;
                getch();
                return;
            }
            oldUser.Delete();
            int result = user.Edit();
            switch (result)
            {
            case -1:
                cout << "保存失败" << endl;
                break;
            case 1:
                cout << "保存成功" << endl;
                break;
            }
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 借阅图书。
     * 清屏并提示用户输入书名和用户名，然后尝试借阅图书。根据操作结果，显示相应的提示信息。
     */
    void BorrowBook() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "图书借阅" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入书名：";
        string title;
        getline(cin, title);
        title = RemoveBlank(title);
        cout << endl;
        if (title.empty())
        {
            cout << "书名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        cout << "请输入用户名：";
        string name;
        getline(cin, name);
        name = RemoveBlank(name);
        cout << endl;
        if (name.empty())
        {
            cout << "用户名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        int result = borrowBook(name, title);
        switch (result)
        {
        case 0:
            cout << "图书不存在" << endl;
            break;
        case -1:
            cout << "图书已借出" << endl;
            break;
        case -2:
            cout << "用户不存在" << endl;
            break;
        case 1:
            cout << "图书借阅成功" << endl;
            break;
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 归还图书。
     * 清屏并提示用户输入书名和用户名，然后尝试归还图书。根据操作结果，显示相应的提示信息。
     */
    void ReturnBook() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "图书归还" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入书名：";
        string title;
        getline(cin, title);
        title = RemoveBlank(title);
        cout << endl;
        if (title.empty())
        {
            cout << "书名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        cout << "请输入用户名：";
        string name;
        getline(cin, name);
        name = RemoveBlank(name);
        cout << endl;
        if (name.empty())
        {
            cout << "用户名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        int result = returnBook(name, title);
        switch (result)
        {
        case 0:
            cout << "图书不存在" << endl;
            break;
        case -1:
            cout << "未借此图书" << endl;
            break;
        case -2:
            cout << "用户不存在" << endl;
            break;
        case 1:
            cout << "图书归还成功" << endl;
            break;
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 查看借阅记录。
     * 清屏并提示用户输入用户名，然后显示该用户的借阅记录。如果用户不存在，显示相应的提示信息。
     */
    void BorrowRecord() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "借阅记录" << endl;
        cout << endl;
        cout << endl;
        cout << "请输入用户名：";
        string name;
        getline(cin, name);
        name = RemoveBlank(name);
        cout << endl;
        if (name.empty())
        {
            cout << "用户名不能为空" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        User user = getUser(name);
        int result = user.name.empty() ? 0 : 1;
        switch (result)
        {
        case 0:
            cout << "用户不存在" << endl;
            break;
        case 1:
            DisplayUser(user);
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 查看十大热门图书。
     * 清屏并显示当前图书馆系统中借阅次数最多的十本图书。
     */
    void TenHotBooks() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "十大热门图书" << endl;
        cout << endl;
        cout << endl;
        vector<Book> books = tenHotBooks();
        if (books.size() == 0)
        {
            cout << "无记录" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        for (int i = 0; i < books.size(); i++)
        {
            cout << "图书" << i + 1 << endl;
            DisplayBook(books[i]);
            cout << endl;
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 查看十大活跃用户。
     * 清屏并显示当前图书馆系统中借阅图书次数最多的十名用户。
     */
    void TenActiveUsers() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "十大活跃用户" << endl;
        cout << endl;
        cout << endl;
        vector<User> users = tenActiveUsers();
        if (users.size() == 0)
        {
            cout << "无记录" << endl;
            cout << endl;
            cout << "按任意键返回" << endl;
            getch();
            return;
        }
        for (int i = 0; i < users.size(); i++)
        {
            cout << "用户" << i + 1 << "：" << users[i].name << endl;
            cout << "借阅次数：" << users[i].borrowTimes << endl;
            cout << endl;
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 删除所有图书。
     * 清屏并提示用户确认是否删除所有图书。根据用户的选择，执行删除操作或取消。
     */
    void DeleteAllBooks() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "确认删除所有图书？(y/n)";
        string c;
        getline(cin, c);
        cout << endl;
        if (c == "y")
        {
            int result = deleteAllBooks();
            switch (result)
            {
            case 1:
                cout << "删除成功" << endl;
                break;
            default:
                cout << "删除失败" << endl;
                break;
            }
        }
        else
        {
            cout << "取消删除" << endl;
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 删除所有用户。
     * 清屏并提示用户确认是否删除所有用户。根据用户的选择，执行删除操作或取消。
     */
    void DeleteAllUsers() const
    {
        system("cls");
        cout << endl;
        cout << endl;
        cout << "确认删除所有用户？(y/n)";
        string c;
        getline(cin, c);
        cout << endl;
        if (c == "y")
        {
            int result = deleteAllUsers();
            switch (result)
            {
            case 1:
                cout << "删除成功" << endl;
                break;
            default:
                cout << "删除失败" << endl;
                break;
            }
        }
        else
        {
            cout << "取消删除" << endl;
        }
        cout << endl;
        cout << "按任意键返回" << endl;
        getch();
    }

    /**
     * @brief 退出程序。
     * 安全退出图书馆系统。
     */
    void Exit() const
    {
        exit(0);
    }

    /**
     * @brief 显示错误信息。
     * 当用户输入无效时，显示错误信息并提示重新输入。
     */
    void Error() const
    {
        cout << endl;
        cout << "无效输入，请重新输入" << endl;
    }
};