#include "Song.h"
int Song::songCount = 0;

Song::Song()
    :Media()
{
    artist = " ";
    duration = -1;
}

Song::Song(char type, string title, string artist, int rating, string genre, int duration, int year)
    :Media(type, title, rating, year, genre)
{
    this->artist = artist;
    this->duration = duration;
}

string Song::getArtist()
{
    return artist;;
}

void Song::setArtist(string a)
{
    artist = a;
}

int Song::getDuration()
{
    return duration;
}

void Song::setDuration(int d)
{
    duration = d;
}

void Song::print(ostream& out)
{
    out << left << setw(40) << title;
    out << left << setw(35) << artist;
    out << left << setw(25) << genre;
    out << left << setw(7) << duration;
    out << left << setw(6) << yearReleased;
    out << left << setw(7) << rating;
}
