#include "MediaLib.h"
#include "Media.h"
using namespace std;

//CODE TO REMOVE TRAILING SPACES AT END OF STRING
//Cited from Peteris on StackOverflow
string remove_spaces(const string& s)
{
	int last = s.size() - 1;
	while (last >= 0 && s[last] == ' ')
		--last;
	return s.substr(0, last + 1);
}

//precondition: take MAP of possible choices
//postcondition: return user choice with check for validity
char PrintMenu(map<pair<int, char>, string> choices) {
	char choice;
	string userInput;
	map<pair<int, char>, string>::iterator mapIt;
	cout << "      MENU CHOICES" << endl;
	
	//iterate through map to print
	for (mapIt = choices.begin(); mapIt != choices.end(); mapIt++) {
		cout << mapIt->first.second << " - " << mapIt->second << endl;
	}
	//check valid char input
	while (true) {
		cout << "\nEnter your choice: ";
		getline(cin, userInput);
		while (userInput.size() > 1) {
			cout << "Please enter single character." << endl;
			getline(cin, userInput);
		}
		
		istringstream inSS(userInput); //stream to char
		inSS >> choice;
		choice = toupper(choice);
		//check if valid choice
		for (mapIt = choices.begin(); mapIt != choices.end(); mapIt++) {
			if (choice == mapIt->first.second) {
				return choice;
			}
		}
		cout << "Invalid choice." << endl; //loop if invalid
	}
}

//precondition: take filename and vector to deposit lines
//postcondition: add lines from file to vector of strings
void ReadFile(string fileName, vector<string>& fileLines) {
	fstream fin;
	fin.open(fileName);
	string tempString;

	//gets whole line of text with spaces, adds to vector
	while (getline(fin, tempString)) {
		fileLines.push_back(tempString);
	}
	fin.close(); //close file
}

//precondition: take line of text and chosen delimited to split string by
//postcondition: returns string as vector of strings by chosen delimit char
vector<string> delimitString(string userText, char delimiter) {
	string temp;
	vector<string> tempStrVector(0);
	istringstream inSS(userText);

	while (inSS.good()) {
		//reads line to delimited into temp string, adds to vector
		getline(inSS, temp, delimiter);
		tempStrVector.push_back(temp);
	}
	return tempStrVector;
}

//precondition: take specified text string and requested total line size
//postcondition: output centered text
void printCenter(string centeredText, int lineSize) {
	int leftRight = (lineSize - centeredText.size()) / 2;
	cout << setw(leftRight) << left << "" << centeredText << setw(leftRight) << right << "";
}


//precondition: take filenames, vec of Media pointers
//post: parse data from file to Media* obj, output errors to log
int readDataFile(string inFile, string outFile, vector<Media*>& mediaLibrary)
{
	vector<string> fileLines(0);
	ReadFile(inFile, fileLines);
	ofstream outFS;
	outFS.open(outFile);
	ostringstream error;

	for (int i = 0; i < fileLines.size(); ++i) {
		try {
			//delimit, pass through Media maker
			vector<string> lineDelimited = delimitString(fileLines.at(i), ',');
			newMedia(lineDelimited, mediaLibrary);
		}
		catch (invalid_argument& excpt) {
			error << "Following entry contains " << excpt.what() << " error:" << endl;
			outFS << error.str() << fileLines.at(i) << "\n" << endl;
			error.str("");
			error.clear();
		}		
		catch (const ios_base::failure excpt) {
			error << "Input error at " << fileLines.at(i);
			outFS << error.str() << "\n" << endl;
			error.str("");
			error.clear();
		}
		catch (...) {
			error << "Unknown error at " << fileLines.at(i);
			outFS << error.str() << "\n" << endl;
			error.str("");
			error.clear();
		}
	}

	return 0;
}

//precondition: take parsed vector of lines of text and Media vec
//postcondition: add info into new Media*, push back to vec
void newMedia(vector<string> line, vector<Media*>& mediaLibrary)
{
	char type = line.at(0)[0];
	string title, genre, director, author, artist;
	int rating, yearReleased, duration, pages;
	vector<string> stars;

	//Media makers for each type, push back to vector
	switch (type) {
		case('B'):
		{
			title = line[1];
			author = line[2];
			rating = stoi(line[3]);
			genre = line[4];
			pages = stoi(line[5]);
			yearReleased = stoi(line[6]);
			Book* tempBook = new Book(type, title, author, rating, genre, pages, yearReleased);
			mediaLibrary.push_back(tempBook);
		}			
			Book::bookCount += 1;      //update counts for
			Media::mediaCount += 1;   //media and subclass
			break;                   //(repeats for each subclass below)
		case('M'):
		{
			title = line[1];
			director = line[2];
			rating = stoi(line[3]);
			genre = line[4];
			duration = stoi(line[5]);
			yearReleased = stoi(line[6]);
			for (int i = 7; i < line.size(); ++i) {
				stars.push_back(remove_spaces(line.at(i))); //removes trailing spaces from csv
			}
			Movie* tempMovie = new Movie(type, title, director, rating, genre, duration, yearReleased, stars);
			mediaLibrary.push_back(tempMovie);
			
		}
			Movie::movieCount += 1;
			Media::mediaCount += 1;
			break;
		case('S'):
		{
			title = line[1];
			artist = line[2];
			rating = stoi(line[3]);
			genre = line[4];
			duration = stoi(line[5]);
			yearReleased = stoi(line[6]);
			Song* tempSong = new Song(type, title, artist, rating, genre, duration, yearReleased);
			mediaLibrary.push_back(tempSong);
		}
			Song::songCount += 1;
			Media::mediaCount += 1;
			break;
		case('Q'):
			return;
	}
}

//precondition: take in vec of Media*
//postcondition: print to screen all formatted Media libraries
void printList(vector<Media*>& mediaLibrary)
{
	printCenter("Your Media Library", 120);
	cout << endl;
	cout << setfill('-') << setw(120) << "" << endl;
	cout.clear();
	cout << setfill(' ');
	printList(mediaLibrary, 'M');
	printList(mediaLibrary, 'S');
	printList(mediaLibrary, 'B');
}

//precondition: take vec of Media* and type to print
//postcondition: print only given type of Media, formatted
void printList(vector<Media*>& mediaLibrary, char type)
{
	cout << endl;
	switch (type) {
	case('M'):
		printCenter("Movies", 120);
		cout << endl;
		cout << left << setw(40) << "Title";
		cout << left << setw(35) << "Director";
		cout << left << setw(25) << "Genre";
		cout << left << setw(7) << "Length";
		cout << left << setw(6) << "Year";
		cout << left << setw(7) << "Rating";
		cout << endl;
		break;
	case('S'):
		printCenter("Songs", 120);
		cout << endl;
		cout << left << setw(40) << "Title";
		cout << left << setw(35) << "Artist";
		cout << left << setw(25) << "Genre";
		cout << left << setw(7) << "Length";
		cout << left << setw(6) << "Year";
		cout << left << setw(7) << "Rating";
		cout << endl;
		break;
	case('B'):
		printCenter("Books", 120);
		cout << endl;
		cout << left << setw(40) << "Title";
		cout << left << setw(35) << "Author";
		cout << left << setw(25) << "Genre";
		cout << left << setw(7) << "Pages";
		cout << left << setw(6) << "Year";
		cout << left << setw(7) << "Rating";
		cout << endl;
		break;
	}
	cout << endl;
	//checks type, prints overrode outstream
	for (int i = 0; i < mediaLibrary.size(); ++i) {
		if (mediaLibrary.at(i)->getType() == type) {
			mediaLibrary.at(i)->print(cout);
			cout << endl;
		}
	}
	cout << endl;
}

//precondition: take vector of Media*, ask for user input on movie name
//postcondition: list all stars from vector in Movie* obj
void listMovieStars(vector<Media*>& mediaLibrary)
{
	string movieTitle;
	cout << "Enter the Movie Name: ";
	getline(cin, movieTitle);
	cout << endl;

	for (int i = 0; i < Media::mediaCount; ++i) {
		if ((mediaLibrary.at(i)->getType() == 'M') && (movieTitle == mediaLibrary.at(i)->getTitle())) {
			Movie* temp = dynamic_cast<Movie*>(mediaLibrary.at(i)); //cast pointer to Movie type if bool true
			cout << setfill('*') << setw(30) << "" << endl;
			cout << "The Stars of the Movie " << movieTitle << " Are:" << endl;
			cout << setfill('*') << setw(30) << "" << endl;
			for (int j = 0; j < temp->GetStars().size(); ++j) {
				cout << temp->GetStars().at(j) << endl;
			}
			cout << setfill(' ');
			cout << endl;
			return;
		}
	}
	cout << setfill(' ');
	cout << "Sorry, but the movie '" << movieTitle << "' is not in your library.\n" << endl;
}

//precondition: take Media* vec, ask user for actor name
//postcondition: print all movies actor appears in
void findMovie(vector<Media*>& mediaLibrary)
{
	vector<string> movieTitles(0);
	string movieActor;
	int movies = 0;
	cout << endl;
	cout << "Enter the Actor Name: ";
	getline(cin, movieActor);

	for (int i = 0; i < Media::mediaCount; ++i) {
		if (mediaLibrary.at(i)->getType() == 'M') {
			Movie* temp = dynamic_cast<Movie*>(mediaLibrary.at(i)); //cast to Movie type
			for (int j = 0; j < temp->GetStars().size(); ++j) {
				//checks if star is in movie, adds movie title to vector<string>
				if (temp->GetStars().at(j) == movieActor) {
					movies += 1;
					movieTitles.push_back(temp->getTitle());
				}
			}
		}
	}
	if (movies == 0) {
		cout << movieActor << " isn't in the cast list of any movie in your library." << endl;
	}
	else {
		//loop if movie count is over 0
		cout << endl;
		cout << setfill('*') << setw(30) << "" << endl;
		cout << movieActor << " Appears in the Following Movies:" << endl;
		cout << setfill('*') << setw(30) << "" << endl;
		cout << setfill(' ');
		for (int m = 0; m < movies; ++m) {
			cout << movieTitles.at(m) << endl;
		}
		cout << endl;
	}
}

//precondition: updated totals of Media objects and subclass objects
//postcondition: print updated count of each
void printTotals()
{
	//prints totals from static class variables
	cout << endl;
	cout << setfill('*') << setw(30) << "" << endl;
	cout << "Media Library Totals:" << endl;
	cout << setfill('*') << setw(30) << "" << endl;
	cout << setfill(' ') << endl;
	cout << left << setw(15) << "Books: " << right << setw(5) << Book::bookCount << endl;
	cout << left << setw(15) << "Movies: " << right << setw(5) << Movie::movieCount << endl;
	cout << left << setw(15) << "Songs: " << right << setw(5) << Song::songCount << endl;
	cout << left << setw(15) << "Total Media: " << right << setw(5) << Media::mediaCount << endl;
	cout << endl;
}

//precondition: Media* vector, user input for type, info for class data
//postcondition: add user Media object to pre-established library
void addUserMedia(vector<Media*>& mediaLibrary)
{
	char type;
	string title, genre, director, artist, author, actor;
	int rating, yearReleased, duration, pages;
	vector<string> stars;
	map<pair<int, char>, string> menu;
	cin.exceptions(istream::failbit | istream::badbit);
	menu[make_pair(0, 'M')] = "Movie";
	menu[make_pair(1, 'B')] = "Book";
	menu[make_pair(2, 'S')] = "Song";
	menu[make_pair(3, 'R')] = "Return to Main Menu";

	try {
		//all input/output for Media data variables
		cout << "\nWhich type of media would you like to add?\n" << endl;
		type = PrintMenu(menu);
		if (type == 'R') { return; }
		cout << "Enter information for given prompt:\n" << endl;
		cout << "Title: ";
		getline(cin >> ws, title);
		cout << "Release Year: ";
		cin >> yearReleased;
		cout << "Genre: ";
		getline(cin >> ws, genre);
		cout << "Rating: ";
		cin >> rating;

		//checks type to get class-specific data
		switch (type) {
		case('M'):
		{
			cout << "Director: ";
			getline(cin >> ws, director);
			cout << "Duration: ";
			cin >> duration;
			cout << "===Enter actors (upper Q to stop)===" << endl;
			getline(cin >> ws, actor);
			while (actor != "Q") {
				stars.push_back(actor);
				getline(cin >> ws, actor);
			}
			Movie* temp = new Movie(type, title, director, rating, genre, duration, yearReleased, stars);
			mediaLibrary.push_back(temp);
			Media::mediaCount += 1;
			Movie::movieCount += 1;
		}
		break;
		case('S'):
		{
			cout << "Artist: ";
			getline(cin >> ws, artist);
			cout << "Duration: ";
			cin >> duration;
			Song* temp = new Song(type, title, artist, rating, genre, duration, yearReleased);
			mediaLibrary.push_back(temp);
			Media::mediaCount += 1;
			Song::songCount += 1;
		}
		break;
		case('B'):
		{
			cout << "Author: ";
			getline(cin >> ws, author);
			cout << "Pages: ";
			cin >> pages;
			Book* temp = new Book(type, title, author, rating, genre, pages, yearReleased);
			mediaLibrary.push_back(temp);
			Media::mediaCount += 1;
			Book::bookCount += 1;
		}
		break;
		}
	}
  cin.exceptions(istream::failbit | istream::badbit);
	catch (...) {
		cout << "Error occured trying to add object to your library. Try again!" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return;
}

//precondition: Media* vector
//postcondition: output random Media* object from library for user
void entertainMe(vector<Media*>& mediaLibrary)
{
	int randomMedia;
	srand(time(0));
	randomMedia = (rand() % Media::mediaCount); //random time-seed based num in range of mediacount
	cout << endl;
	cout << "Here's a random pick from your library:" << endl;
	//gives message based on type of Media, then the piece of Media to suggest to user
	switch (mediaLibrary.at(randomMedia)->getType()) {
		case('M'):
		{
			Movie* temp = dynamic_cast<Movie*>(mediaLibrary.at(randomMedia));
			cout << "Movie night! Here's something to watch!" << endl;
			cout << temp->getTitle() << ", directed by " << temp->getDirector() << ". Enjoy!" << endl;
		}
			break;
		case('B'):
		{
			Book* temp = dynamic_cast<Book*>(mediaLibrary.at(randomMedia));
			cout << "Sit down, relax, and grab a book!" << endl;
			cout << temp->getTitle() << ", written by " << temp->getAuthor() << ". Enjoy!" << endl;
		}
			break;
		case('S'):
		{
			Song* temp = dynamic_cast<Song*>(mediaLibrary.at(randomMedia));
			cout << "Time to jame out to " << temp->getTitle() << " by " << temp->getArtist() << endl;
		}
			break;
	}
	return;
}

