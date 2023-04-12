#pragma once
#include "Media.h"
class Book :
    public Media
{
private:
    string author;
    int pages;
    
public:
    static int bookCount;

    Book();
    Book(char, string, string, int, string, int, int);

    string getAuthor();
    void setAuthor(string);

    int getPages();
    void setPages(int);

    void print(ostream& out);
};

