#include "GUI.hpp"
#include <unistd.h>

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
    Exit
};

bool IsPureNumber(const string &input)
{
    for (char c : input)
    {
        if (c < '0' || c > '9')
        {
            return false;
        }
    }
    return true;
}

int main()
{
    if (!filesystem::exists("./data/book/"))
    {
        filesystem::create_directories("./data/book/");
    }
    if (!filesystem::exists("./data/user/"))
    {
        filesystem::create_directories("./data/user/");
    }
    GUI gui;
    while (true)
    {
        gui.ShowMenu();
        string input;
        int choice;
        getline(cin, input);
        if (!IsPureNumber(input) || input.empty())
        {
            gui.Error();
            sleep(1);
            continue;
        }
        choice = stoi(input);
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
        case Exit:
            gui.Exit();
            return 0;
        default:
            gui.Error();
            sleep(1);
            break;
        }
    }
    return 0;
}