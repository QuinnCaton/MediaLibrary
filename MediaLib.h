#pragma once
#include "Media.h"
#include "Book.h"
#include "Song.h"
#include "Movie.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cstdlib>
#include <ctime> 

string remove_spaces(const string&); //CODE FROM: Peteris on StackOverflow
void ReadFile(string fileName, vector<string>& fileLines); //Done
vector<string> delimitString(string userText, char delimiter); //Done
char PrintMenu(map<pair<int, char>, string>); //Done
void printCenter(string centeredText, int lineSize); //Done

int readDataFile(string, string, vector<Media*>&); //Done
void newMedia(vector<string>, vector<Media*>&); //Done

void printList(vector<Media*>&);
void printList(vector<Media*>&, char type);

void listMovieStars(vector<Media*>&);
//FIXME: Refactor code from movie project
void findMovie(vector<Media*>&);
//FIXME: Refactor code from movie project

void printTotals();
void addUserMedia(vector<Media*>&);
void entertainMe(vector<Media*>&);
