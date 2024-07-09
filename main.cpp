#include "GUI.hpp"

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

bool IsPureNumber(const string &input)
{
    return all_of(input.begin(), input.end(), ::isdigit);
}

int main()
{
    GUI library;
    bool error = false;
    system("chcp 65001");

    while (true)
    {
        if (!filesystem::exists("./data/book/"))
            filesystem::create_directories("./data/book/");
        if (!filesystem::exists("./data/user/"))
            filesystem::create_directories("./data/user/");

        library.ShowMenu();
        if (error)
            library.Error();

        string input;
        int choice;
        getline(cin, input);
        if (!IsPureNumber(input) ||
            input.empty() ||
            (choice = stoi(input)) > Exit ||
            choice < AddBook)
        {
            error = true;
            continue;
        }

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
            library.Exit();
        }
        error = false;
    }
    return 0;
}