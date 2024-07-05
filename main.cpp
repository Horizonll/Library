#include "GUI.hpp"
#include <iostream>
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
int main()
{
    GUI gui;
    while (true)
    {
        gui.ShowMenu();
        int choice;
        cin >> choice;
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
            break;
        }
    }
    return 0;
}