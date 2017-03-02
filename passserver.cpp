//#include "passserver.h"
PassServer::PassServer(size_t size){

	hasht = new HashTable<std::string, std::string>(size);
	
}

PassServer::~PassServer(){
	delete hasht;
}

bool PassServer::load(const char *filename){
if(hasht->load(filename) == true) return true;

return false;

}


bool PassServer::addUser(std::pair<string,  string> & kv){

std::pair<string, string> temp;
temp.first = kv.first;
temp.second = encrypt(kv.second);
if(hasht->insert(temp) == true) return true;
else
return false;


}

bool PassServer::addUser(std::pair<string, string> && kv){
std::pair<string, string> temp;
temp.first = kv.first;
temp.second = encrypt(kv.second);
if (hasht->insert(temp)) return true;

return false;
}

bool PassServer::removeUser(const string & k){
char *temp;
temp = new char[k.size()];
for (unsigned int i = 0; i < k.size(); i++)
temp[i] = k[i];
if (hasht->remove(temp) == true){
return true;
}
else
return false;

}


bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword){
std::pair<string, string> zoop;
zoop.first = p.first;
zoop.second = encrypt(p.second);
if (hasht->match(zoop)){
hasht->remove(p.first);
std::pair<string, string> temp;
temp.first = p.first;
temp.second = encrypt(newpassword);
addUser(temp);
return true;

}

return false;
}

bool PassServer::find(const string & user){

return hasht->contains(user);
}

void PassServer::dump(){
hasht->dump();
}


bool PassServer::write_to_file(const char *filename){
	hasht->write_to_file(filename);
return true;
}



string PassServer::encrypt(const string & str){
  const char *const pass = "$1$########";
  char * c = new char[str.size()];;
  for (unsigned int i = 0; i < str.size(); i++){
    c[i] = str[i];
  }
  string s(crypt(c, pass));

 return s;
}

size_t PassServer::size(){
	return(hasht->getSize());


}
