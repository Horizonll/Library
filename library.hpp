#include "GUI.hpp"

class Library : public GUI
{
public:
    void CheckData()
    {
        if (!filesystem::exists("./data/book/"))
            filesystem::create_directories("./data/book/");
        if (!filesystem::exists("./data/user/"))
            filesystem::create_directories("./data/user/");
    }
};