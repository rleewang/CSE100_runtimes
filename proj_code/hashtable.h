#include <list>
#include <iostream>
#include <fstream>

#ifndef HASHTABLE_H
#define HASHTABLe_H

//Just something to put all of our hashing functions into and call from an external function where we do the actual test

class hashtable {
  public:
    //Basic hash table functions
    hashtable(int size);
    ~hashtable();
    int Size();
    int Insert(long long key);
    int Delete(long long key);
    int Search(long long key);
    //Hash selection functions & hash functions
    void selectHash(int type, int type2);
    int hashFunction(long long key, int type, int type2, int i);
    long long hash1(long long key);
    long long hash2(long long key);
    long long hash3(long long key);
    long long hash4(long long key);
    long long hash5(long long key);
    //Other functions
    void genKeys(long long *s, long long *d, long long *u, int n);
    void clusterRunLengths(int* runlengths);
    void writeTable(std::ofstream &file); //Debugging purposes
    void resetTable();
    void genNonRandom(int n, int mode,long long *s, long long *d, long long *u);
  private:
    int primary;	//primary hash type
    int secondary;	//secondary hash type
    int size;
    long long* table;
};

#endif
