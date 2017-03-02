template <typename K, typename V>						
HashTable<K, V>::HashTable(size_t size){
   if(prime_below(size) == 0){ theLists.resize(101);
   cout << "Table size: 101";}
   else{
   cout << prime_below(size);
   theLists.resize(prime_below(size));   
   }
}
template <typename K, typename V>
HashTable<K, V>::~HashTable(){
	clear();

}
template<class InputIterator, class T>
  InputIterator find (InputIterator first, InputIterator last, const T& val)
  {
    while (first!=last) {
        if (first->first==val) return first;
	    ++first;
	      }
	        return last;
		}
template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k){/////////////////////////////////////////////////
	auto & whichList = theLists[myhash(k)];

	auto litr = whichList.begin();
	for (auto &x: whichList){
		if (litr->first == k )return true;
		x = x;
	++litr;
	}
	return false;
	
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const{///////////////////////////////////////////////
	auto & whichList = theLists[myhash(kv.first)];
	K what = kv.first;
 	K  what2 = kv.second;

	auto litr = whichList.begin();
	auto litr2 = whichList.end();
	while (litr != litr2){
	   auto ew = litr->first;
	   auto ew2 = litr->second;

	   if (ew == what && ew2 == what2) return true;
	  ++litr;
	}
	 return false ;
//	return find(begin(whichList), end(whichList), kv) != end(whichList);

}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv){

	auto & whichList = theLists[myhash(kv.first)];
//	if (find(whichList.begin(), whichList.end(), kv) != whichList.end())
//		return false;

	auto litr = whichList.begin();
	auto litr2 = whichList.end();

	while (litr != litr2){
	  if (contains(kv.first)){
	       cout << "\nError: Duplicate key '" << kv.first << "', duplicate key ignored";
	   return false;}
	litr++;

	}




	whichList.push_back(kv);
					
	if (++currentSize > theLists.size())
		rehash();
						
	return true;
				 				
}

template <typename K, typename V>
bool HashTable<K, V>::insert (std::pair<K,  V> && kv){

	auto & whichList = theLists[myhash(kv.first)];
	//if (find(begin(whichList), end(whichList), kv) != end(whichList))
	//	return false;
	auto litr = whichList.begin();
	auto litr2 = whichList.end();

	while (litr != litr2){
	  if (*litr == kv) return false;

	litr++;
	}
	whichList.push_back( std::move(kv));
					
	if (++currentSize > theLists.size())
		rehash();
						
	return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k){
 auto & whichList = theLists[ myhash( k ) ]; 
 auto itr = find( begin( whichList ), end( whichList ), k ); 
 if( itr == end( whichList ) ) 
 return false; 
 
 whichList.erase( itr ); 
 --currentSize; 
 return true;
/*

	auto & whichList = theLists[myhash(k)];
	auto itr = find(begin(whichList), end(whichList), k);
	auto itr = whichList.begin();
	//auto itr2 = theLists.end();

	   whichList.erase(itr);
	   --currentSize;
	   return true;
	
	   return false;
*/
}

template <typename K, typename V>
void HashTable<K, V>::clear(){
	makeEmpty();
}
template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename){
	std::ifstream ifs(filename);
	std::pair<std::string, std::string> tempPair;
	std::string ts1, ts2;
if (ifs.fail()) return false;
else
	while(ifs >> ts1 >> ts2){
	tempPair = std::make_pair(ts1, ts2);
	insert(tempPair);

	}
	ifs.close();
	return true;

}
template <typename K, typename V>
void HashTable<K, V>::dump(){
	unsigned int l = 0;
	for(auto & lists: theLists){
		std::cout << "V[" << l << "] "; 
		for (auto i : lists){
		   std::cout << i.first << " " << i.second;
		   if (lists.begin() != lists.end()) std::cout << ": ";
		 }
		std::cout << "\n";
		l++;
	}
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename){
   std::ofstream ofs;
   ofs.open(filename, std::ofstream::out | std:: ofstream::app);

	for(auto & lists: theLists){
		for (auto i : lists){
		if (!i.first.empty());
		   ofs << i.first << " " << i.second << "\n";
		 }
		//ofs << "\n";
	}
	return true;
}
   
template <typename K, typename V>
void HashTable<K, V>::makeEmpty(){
    for (auto & thisList : theLists) {
		thisList.clear();	
    }

}
template <typename K, typename V>
void HashTable<K, V>::rehash(){
   auto oldLists = theLists;


	theLists.resize(prime_below(2 * theLists.size()));
 		for (auto & thisList: theLists)
		thisList.clear();

		
		currentSize = 0;
		for (auto & thisList : oldLists)
		for (auto & x : thisList)
		insert(std::move(x));										

}
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k){
/*
 unsigned int hashVal = 0; 
for (char c: k) 
 hashVal = 37 * hashVal + c; 
 return hashVal % theLists.size();;
*/
   static std::hash<K> hf; 
   return hf( k) % theLists.size( );
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const{
/*
 unsigned int hashVal = 0; 
for (char c: k) 
 hashVal = 37 * hashVal + c; 
 return hashVal % theLists.size();;
*/
   static std::hash<K> hf; 
   return hf( k) % theLists.size( );
}
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

template <typename K, typename V>
int HashTable<K,V>::getSize(){
   return (theLists.size());

}
