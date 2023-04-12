#include "Book.h"
int Book::bookCount = 0;

Book::Book()
    :Media()
{
    author = " ";
    pages = -1;
}

Book::Book(char type, string title, string author, int rating, string genre, int pages, int year)
    :Media(type, title, rating, year, genre)
{
    this->author = author;
    this->pages = pages;
}

string Book::getAuthor()
{
    return author;
}

void Book::setAuthor(string a)
{
    author = a;
}

int Book::getPages()
{
    return pages;
}

void Book::setPages(int p)
{
    pages = p;
}

void Book::print(ostream& out)
{
    out << left << setw(40) << title;
    out << left << setw(35) << author;
    out << left << setw(25) << genre;
    out << left << setw(7) << pages;
    out << left << setw(6) << yearReleased;
    out << left << setw(7) << rating;
}
