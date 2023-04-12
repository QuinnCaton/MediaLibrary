#include <iostream>
#include <utility>
#include "MediaLib.h"
using namespace std;

int main()
{
    vector<string> fileLines;
    vector<Media*> mediaLibrary(0);
    map<pair<int, char>, string> menu;
    menu[make_pair(0,'M')] = "Print Movie List";
    menu[make_pair(1,'B')] = "Print Book List";
    menu[make_pair(2,'S')] = "Print Song List";
    menu[make_pair(3,'A')] = "Print All Media";
    menu[make_pair(4,'F')] = "Find the Movie a Star is in";
    menu[make_pair(5,'G')] = "Print Stars for a Given Movie";
    menu[make_pair(6,'T')] = "Print Media Counts";
    menu[make_pair(7,'N')] = "Add new Media Item";
    menu[make_pair(8, 'E')] = "Entertain Me!";
    menu[make_pair(9,'Q')] = "Quit";

    //read file to vector of str
    ReadFile("mediaList.txt", fileLines);
    //parse into Media* objects
    readDataFile("mediaList.txt", "mediaLibErrors.txt", mediaLibrary);

    while (true) {
        try {
            char choice;
            cout << endl;
            choice = PrintMenu(menu);
            switch (choice) {
                case('M'):
                    printList(mediaLibrary, 'M');
                    break;
                case('B'):
                    printList(mediaLibrary, 'B');
                    break;
                case('S'):
                    printList(mediaLibrary, 'S');
                    break;
                case('A'):
                    printList(mediaLibrary);
                    break;
                case('F'):
                    findMovie(mediaLibrary);
                    break;
                case('G'):
                    listMovieStars(mediaLibrary);
                    break;
                case('T'):
                    printTotals();
                    break;
                case('N'):
                    addUserMedia(mediaLibrary);
                    break;
                case('E'):
                    entertainMe(mediaLibrary);
                    break;
                case('Q'):
                    cout << "Thank you!" << endl;
                    return 0;
            }
        }
        catch (runtime_error& err) {
            cout << err.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        catch (...) {
            cout << "Unknow error has occurred!" << endl;
        }
    }
    return 0;
}
