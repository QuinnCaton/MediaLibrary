#pragma once
#include "Media.h"
class Movie :
    public Media
{
private:
    string director;
    int duration;
    vector<string>stars;
public:
    static int movieCount;

    Movie();
    Movie(char, string, string, int, string, int, int, vector<string>);

    string getDirector();
    void setDirector(string);

    int getDuration();
    void setDuration(int);

    void SetStars(vector<string>);
    vector<string> GetStars();

    void print(ostream& out);
};

