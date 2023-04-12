#pragma once
#include "Media.h"
class Song :
    public Media
{
private:
    string artist;
    int duration;
public:
    static int songCount;

    Song();
    Song(char, string, string, int, string, int, int);

    string getArtist();
    void setArtist(string);
    
    int getDuration();
    void setDuration(int);

    void print(ostream& out);
};

