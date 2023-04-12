#include "Media.h"

int Media::mediaCount = 0;

Media::Media()
{
    type = ' ';
    title = " ";
    rating = -1;
    yearReleased = -1;
    genre = " ";
}

Media::Media(char type, string title, int rating, int year, string genre)
{
    this->type = type;
    this->title = title;
    this->rating = rating;
    yearReleased = year;
    this->genre = genre;
}

char Media::getType()
{
    return type;
}

void Media::setType(char t)
{
    type = t;
}

string Media::getTitle()
{
    return title;
}

void Media::setTitle(string t)
{
    title = t;
}

string Media::getGenre()
{
    return genre;
}

void Media::setGenre(string g)
{
    genre = g;
}

int Media::getRating()
{
    return rating;
}

void Media::setRating(int r)
{
    rating = r;
}

int Media::getYear()
{
    return yearReleased;
}

void Media::setYear(int y)
{
    yearReleased = y;
}

void Media::print(ostream& out)
{
    out << "Media: " << title;
}
