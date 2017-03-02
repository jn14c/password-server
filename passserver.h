#ifndef PASSSERVER_H
#define PASSSERVER_H
#include <crypt.h>
#include <iostream>
#include <string>
#include "hashtable.h"
#include <cstdlib>
#include <curses.h>
using namespace cop4530;
class PassServer{
public:

PassServer(size_t size = 101);
~PassServer();
bool load(const char *filename);
bool addUser(std::pair<string,  string> & kv);
bool addUser(std::pair<string, string> && kv);
bool removeUser(const string & k);
bool changePassword(const pair<string, string> &p, const string & newpassword);
bool find(const string & user);
void dump();
size_t size();
bool write_to_file(const char *filename);

private:
//bool write_to_file(const char *filename);
HashTable<std::string, std::string> *hasht;
string encrypt(const string & str);
};
#include "passserver.cpp"

#endif
