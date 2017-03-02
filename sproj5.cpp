#include <iostream>
#include <string>
#include <curses.h>
#include <cstdlib>
#include <crypt.h>
#include "passserver.h"

//using namespace cop4530;
using namespace std;

string getSPass(const int & a);
void Menu();
void funcCall(const char & selection);
string getSPass(const int & a);

int main(){
	
char selection;
int hashSize;
do{
cin.clear();
cout << "Enter preferred hash table capacity: ";
cin >> hashSize;
}while (cin.fail());
PassServer passwordServ(hashSize);
do{

Menu();
cin >> selection;


	switch (selection){
	case 'l':{
	   char  filename[25];
	   cout << "Enter password file name to load from: ";
	   cin >> filename;
           if(passwordServ.load(filename)) cout << " ";
	   else cout << "Error: Cannot open file " << filename << "\n";
	}
	break;

	case 'a': {
	   string user, pass;
	   cout << "Enter username: ";
	   cin >> user;
	   pass = (getSPass(0));
	   std::pair<std::string, std::string> adder;
	   adder = make_pair(user, pass);
           passwordServ.addUser(adder);
	}		
	break;

	case 'r':{
	   string user;
	   cout << "Enter username: ";
	   cin >> user;
	  // string pass(getSPass(0));
	if(passwordServ.removeUser(user)) cout << "User "  << user << " removed\n";
	else  cout << "*****Error: User not found.  Could not delete user\n"; 

	}
	break;

	case 'c': {
	   string user;
	   cout << "Enter username: ";
	   cin >> user;
	   string pass(getSPass(0));	
	   string newPass(getSPass(1));
	   std::pair<std::string, std::string> adder;
	   adder.first = user;
	   adder.second = pass;
	   if(passwordServ.changePassword(adder, newPass)) cout << "Password changed for user " << user << "\n";
	   else cout << "*****Error: Could not change user password\n";
	}	
	break;

	case 'f': {
	   string user;
	   cout << "Enter username    :";
	   cin >> user;

	if (passwordServ.find(user))cout << "User '" << user << "' found\n";
	else cout << "User '" << user << "' not found\n";
	}		
	break;

	case 'd': passwordServ.dump();		
	break;

	case 's': cout << passwordServ.size();		
	break;

	case 'w':{
	   char filen[25];
	   string file;
	   cout << "Enter password file name to write to: ";
	   cin >> filen;
		passwordServ.write_to_file(filen);
	  }	
	break;

	case 'x': exit(0); 		
	break;

	default:{ }
	}
}while (!cin.eof());
	return 0;
}

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}


string getSPass(const int & a){
    char password[25];
    initscr();
    echo();
    curs_set(0);
    noecho();
    if (a == 0) printw("Enter password: ");
    else printw("Enter new password: ");
    cin >> password;
    string s(password);
    clear();
    endwin();
    curs_set(1);
	return s;
}

