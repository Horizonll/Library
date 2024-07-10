using namespace std;

class Base
{
public:
    virtual int Add() const = 0;
    virtual void Save() const = 0;
    virtual int Delete() const = 0;
    virtual int Edit() const = 0;
};