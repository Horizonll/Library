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
    Exit
};

bool IsPureNumber(const string &input)
{
    return all_of(input.begin(), input.end(), ::isdigit);
}

int main()
{
    if (!filesystem::exists("./data/book/"))
        filesystem::create_directories("./data/book/");
    if (!filesystem::exists("./data/user/"))
        filesystem::create_directories("./data/user/");
    GUI gui;
    bool error = false;
    system("chcp 65001");

    while (true)
    {
        gui.ShowMenu();
        if (error)
            gui.Error();

        string input;
        int choice;
        getline(cin, input);
        if (!IsPureNumber(input) || input.empty() || (choice = stoi(input)) > Exit || choice < AddBook)
        {
            error = true;
            continue;
        }

        switch (choice)
        {
        case AddBook:
            gui.AddBook();
            break;
        case DeleteBook:
            gui.DeleteBook();
            break;
        case SearchBook:
            gui.SearchBook();
            break;
        case EditBook:
            gui.EditBook();
            break;
        case AddUser:
            gui.AddUser();
            break;
        case DeleteUser:
            gui.DeleteUser();
            break;
        case SearchUser:
            gui.SearchUser();
            break;
        case EditUser:
            gui.EditUser();
            break;
        case BorrowBook:
            gui.BorrowBook();
            break;
        case ReturnBook:
            gui.ReturnBook();
            break;
        case BorrowRecord:
            gui.BorrowRecord();
            break;
        case TenHotBooks:
            gui.TenHotBooks();
            break;
        case TenActiveUsers:
            gui.TenActiveUsers();
            break;
        case Exit:
            gui.Exit();
            return 0;
        }
        error = false;
    }
    return 0;
}