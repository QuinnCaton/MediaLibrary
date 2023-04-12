#include "Movie.h"
int Movie::movieCount = 0;
Movie::Movie()
    :Media()
{
    director = " ";
    duration = -1;
    
}

Movie::Movie(char type, string title, string director, int rating, string genre, int duration, int year, vector<string> stars)
    :Media(type, title, rating, year, genre)
{
    this->director = director;
    this->duration = duration;
    this->stars = stars;
}

string Movie::getDirector()
{
    return director;
}

void Movie::setDirector(string d)
{
    director = d;
}

int Movie::getDuration()
{
    return duration;
}

void Movie::setDuration(int d)
{
    duration = d;
}

void Movie::SetStars(vector<string> stars)
{
    this->stars = stars;
}

vector<string> Movie::GetStars()
{
    return stars;
}

void Movie::print(ostream& out)
{
    out << left << setw(40) << title;
    out << left << setw(35) << director;
    out << left << setw(25) << genre;
    out << left << setw(7) << duration;
    out << left << setw(6) << yearReleased;
    out << left << setw(7) << rating;
}

