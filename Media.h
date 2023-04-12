#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class Media
{
protected:
	char type;
	string title, genre;
	int rating, yearReleased;
public:
	static int mediaCount;

	Media();
	Media(char, string, int, int, string);

	char getType();
	void setType(char);

	string getTitle();
	void setTitle(string);

	string getGenre();
	void setGenre(string);

	int getRating();
	void setRating(int);

	int getYear();
	void setYear(int);

	virtual void print(ostream& out);
	//FIXME: Create Definition
};

