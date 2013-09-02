#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include "hashtablechain.h"

//using namespace std;

hashtable::hashtable(int n) {
  table = new list<long long >[n];
  size = n;
}

hashtable::~hashtable(){

}
int hashtable::Size() {
  return size;
}

int hashtable::Insert(long long key) {
  int n = hashFunction(key, primary, 0);
  int miss = 0;
  if(table[n].empty()) {
    table[n].push_front(key);
  } else {
    while(miss < size && !(table[n].empty()) {
      miss++;
      //This was used in lab to do double hashing for open addressing hash tables
      n = hashFunction(key, primary, miss);
    }
    if(miss < size) { 
      table[n].pus_front(key);
    } else {
      cout << "Unable to insert key " << key << endl;
      return 0;
    }
  }
  return 1;
}

int hashtable::Delete(long long key) {
  int n = hashFunction(key, primary, 0);
  list<long long>::iterator i;
	for(i = table[n].begin(); i != table[n].end(); i++) {
		if(*i == key){
			table[n].erase(i);
			break;
		}
	}
  }	else {
    while(table[n] != key) {
      n = hashFunction(key, primary, miss);
      for(i = table[n].begin(); i != table[n].end(); i++) {
			if(*i == key){
				table[n].erase(i);
				break;
			}
		}
    }
     else {
      cout << "Unable to delete key " << key << endl;
    }

    return 0;
  }
  return 1;
}

int hashtable::Search(long long key) {
  int n = hashFunction(key, primary, 0);
  int temp = n;
//  cerr << n << "\t";
  int miss = 0;
  if(table[n] == key) {
    return miss;
  } else {
    while(miss < size && !(table[n].empty()) {
      miss++;
      n = hashFunction(key, primary, miss);
      if(n == temp)
        break; //I've already checked this one. This means I'm just cycling through again, so exit
      if(table[n] == -1)
        break;
//      cerr << n << "\t";
    }
    return miss;
//    if(table[n] == key) {
//      return n;
//    }
//    return -1;
  }
}

void hashtable::selectHash(int type) {
  primary = type;
}

int hashtable::hashFunction(long long key, int type, int i) {
/*
 *Using double hashing, we have 2 primary hash functions determined by type
 *and 3 secondary hash functions determined by type2. i is the number of misses for re-hashing
 */
  long long h1;
  int n = size;
  if(type == 1) {
    h1 = hash1(key);
  } else if(type == 2) {
    h1 = hash2(key);
  }

//Not sure if we are supposed to be using double hashing or not. Just a temporary decision
  return h1; 
}

long long hashtable::hash1(long long key) {
	//assuming division hash method: h(k) = k mod m
  long long result = key % size;
  return result;
}

long long hashtable::hash2(long long key) {
	//A = (√5 − 1)/2: h1(k) = ⌊m(kA − ⌊kA⌋)⌋.
	double A = (sqrt(5) -1)/2;
	long double temp = floor(key*A);
	long long result = floor(size *(key*A - temp));
	return result;
}

void hashtable::genKeys(long long *s, long long *d, long long *u, int n){
	int ten_5=10*10*10*10*10;
  int j;
  long long result;
	long long k=size*ten_5;
  cout << "Generating keys from a range of 1 to " << k << endl;
	srand(time(0));
  list<long long> temp [100000];
  list<long long>::iterator it;
  bool found;

  for(int i = 0; i < n/2; i++) {
    result = rand()%k+1;
    while(true) {
      found = false;
      j = result % 100000;
      for(it = temp[j].begin(); it != temp[j].end(); it++) {
        if(*it == result) {
          //used already, choose next value and start over
          found = true;
          result = rand()%k+1;
          break;
        }
      }
      if(!found) {
        temp[j].push_back(result);
        break;
      }
    }
    s[i] = result;
  }

  for(int i = 0; i < n/2; i++) {
    result = rand()%k+1;
    while(true) {
      found = false;
      j = result % 100000;
      for(it = temp[j].begin(); it != temp[j].end(); it++) {
        if(*it == result) {
          //used already, choose next value and start over
          found = true;
          result = rand()%k+1;
          break;
        }
      }
      if(!found) {
        temp[j].push_back(result);
        break;
      }
    }
    d[i] = result;
  }

  for(int i = 0; i < ten_5; i++) {
    result = rand()%k+1 + k;

    while(true) {
      found = false;
      j = result % 100000;
      for(it = temp[j].begin(); it != temp[j].end(); it++) {
        if(*it == result) {
          //used already, choose next value and start over
          found = true;
          result = rand()%k+1 + k;
          break;
        }
      }
      if(!found) {
        temp[j].push_back(result);
        break;
      }
    }
    u[i] = result;
  }
 
  for(int i = 0; i < 100000; i++) {
    temp[i].clear();
  }
}

void hashtable::clusterRunLengths(int* runlengths) {
  for(int i = 0; i < size; i++) {
    runlengths[i] = 0;
  }
  int count = 0;
  for(int i = 0; i < size; i++) {
  	if(table[i] == -1 || table[i] == -2) {
      if(i == 0 && count == 0) {
        continue;
      } else {
      	runlengths[count-1]++;
      	count = 0;
      }
    } else {
    	count++;
    }
  }
}

void hashtable::writeTable(std::ofstream &file) {
  for(int i = 0; i < size; i++) {
    file << table[i] << " ";
  }
  file << "\n";
}

void hashtable::resetTable() {
  for(int i = 0; i < size; i++) {
    table[i] = -1; //set table to NIL
  }
}
void hashtable::genData(){
	ofstream fuk;
	fuk.open("NonRanData.txt");
	for(int i=0;i<996148;i++){
		fuk<<i+1<<" ";
	}
	fuk<<endl;
	int ten_5=10*10*10*10*10;
	for(int i=0;i<ten_5;i++){
		fuk<<i+1<<" ";
	}
	fuk<<endl;
	fuk.close();
}
