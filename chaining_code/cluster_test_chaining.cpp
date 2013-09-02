#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <sys/time.h>
#include "hashtablechain.h"

//using namespace std;

int main() {
	long long *s; //keys to insert
	long long *d; //keys to delete
	long long *u; //keys to search
  int* clusterLengths;
	int ten_5=10*10*10*10*10;
	int n;//number of keys to generate, must be even
  int size;
  int two_20 = 1048576;
  int misses = 0;
  float alpha; //alpha
  float a[6] = {0.05, 0.1, 0.5, 0.8, 0.9, 0.95};
  double diff, max, min, stdev;
  ofstream times, stats, misses1, clusters;

  cout << "Allocating hash table" << endl;
  hashtable* table = new hashtable(two_20);
  cout << "Successfully allocated space" << endl;
  struct timeval start,end,it_start, it_end;	// time structure for starting and ending time 
  size = table->Size();
  clusterLengths = new int[size];

  times.open("times.txt");
//  stats.open("stats.txt");
//  misses.open("misses.txt");
//  clusters.open("clusters.txt");

  for(int i = 0; i < 6; i++) {
    alpha = a[i];
    n = alpha*size;
    if(n % 2 != 0) {
      n--;
    }
    times << "--------------------------------------------------------------------------------------------------" << endl;
    times << "--------------------------------------------------------------------------------------------------" << endl;
    times << "Generating " << n << " keys with a table size of " << size << endl;
    cout << "Generating " << n << " keys | Alpha = " << alpha << endl;
    times << "ALPHA = " << alpha << endl;
    times << "--------------------------------------------------------------------------------------------------" << endl;
    times << "--------------------------------------------------------------------------------------------------" << endl;
    //Use the same keys for each hash combination
   	s = new long long[n/2];
  	d = new long long[n/2];
	  u = new long long[ten_5];

    cout << "Generating " << n << " keys" << endl;
  	table->genKeys(s,d,u,n);

    //Loop through possible primary and secondary hash combinations
    for(int type = 1; type <= 2; type++) {
        table->resetTable();
        cout << "Selecting hashes " << type << endl;
        table->selectHash(type);
        times << "Runtimes for primary hash type " << type << " and secondary hash type " << type2 << endl;
        times << "***********************************************************************" << endl;
        //Insert keys into hash table
        for(int i = 0; i < n/2; i++) {
          table->Insert(s[i]);
          table->Insert(d[i]);
        }

        max = 0;
        min = 1;
        stdev = 0;
        misses = 0;
        times << "Successful search times prior to deletion:" << endl;
        gettimeofday(&start, NULL);
        for(int i = 0; i < n/2; i++) {
          gettimeofday(&it_start, NULL);
          misses += table->Search(s[i]);
          gettimeofday(&it_end, NULL);
          diff = (double)(it_end.tv_sec - it_start.tv_sec) + (it_end.tv_usec - it_start.tv_usec)/1000000.0;
          if(diff > max) {
            max = diff;
          }
          if(diff < min) {
            min = diff;
          }
          stdev += diff*diff;
        }
        gettimeofday(&end, NULL);
        stdev /= n/2;
        stdev = sqrt(stdev);
        times << "Standard deviation: " << stdev << endl;
        times << "Maximum: " << max << endl;
        times << "Minimum: " << min << endl;
        times << "Accumulative time: ";
        diff = (double)(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
        times << diff << endl;
        times << "Average time: " << diff/(n/2) << endl;
        times << "Average misses: " << misses/(n/2) << endl;
        times << "***********************************************************************" << endl;

        max = 0;
        min = 1;
        stdev = 0;
        misses = 0;
        cout << "Searching from U pre-deletion" << endl;
        times << "Unsuccessful search times prior to deletion: " << endl;
        gettimeofday(&start, NULL);
        for(int i = 0; i < ten_5; i++) {
          if(i % 10000 == 0)
            cout << "iteration " << i << endl;
          gettimeofday(&it_start, NULL);
          misses += table->Search(u[i]);
          gettimeofday(&it_end, NULL);
          diff = (double)(it_end.tv_sec - it_start.tv_sec) + (it_end.tv_usec - it_start.tv_usec)/1000000.0;
          if(diff > max) {
            max = diff;
          }
          if(diff < min) {
            min = diff;
          }
          stdev += diff*diff;
        }
        gettimeofday(&end, NULL);
        stdev /= n/2;
        stdev = sqrt(stdev);
        times << "Standard deviation: " << stdev << endl;
        times << "Maximum: " << max << endl;
        times << "Minimum: " << min << endl;
        times << "Accumulative time: ";
        diff = (double)(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
        times << diff << endl;
        times << "Average time: " << diff/(ten_5) << endl;
        times << "Average misses: " << misses/(ten_5) << endl;
        times << "***********************************************************************" << endl;

        //Delete keys from the hash table
        for(int i = 0; i < n/2; i++) {
          table->Delete(d[i]);
        }

        max = 0;
        min = 1;
        stdev = 0;
        misses = 0;
        times << "Successful search times post deletion: " << endl;
        gettimeofday(&start, NULL);
        for(int i = 0; i < n/2; i++) {
          gettimeofday(&it_start, NULL);
          misses += table->Search(s[i]);
          gettimeofday(&it_end, NULL);
          diff = (double)(it_end.tv_sec - it_start.tv_sec) + (it_end.tv_usec - it_start.tv_usec)/1000000.0;
          if(diff > max) {
            max = diff;
          }
          if(diff < min) {
            min = diff;
          }
          stdev += diff*diff;
        }
        gettimeofday(&end, NULL);
        stdev /= n/2;
        stdev = sqrt(stdev);
        times << "Standard deviation: " << stdev << endl;
        times << "Maximum: " << max << endl;
        times << "Minimum: " << min << endl;
        times << "Accumulative time: ";
        diff = (double)(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
        times << diff << endl;
        times << "Average time: " << diff/(n/2) << endl;
        times << "Average misses: " << misses/(n/2) << endl;
        times << "***********************************************************************" << endl;

        max = 0;
        min = 1;
        stdev = 0;
        misses = 0;
        cout << "Searching from U post-deletion" << endl;
        times << "Unsuccessful search times post deletion: " << endl;
        gettimeofday(&start, NULL);
        for(int i = 0; i < ten_5; i++) {
          if(i % 10000 == 0)
            cout << "iteration " << i << endl;
          gettimeofday(&it_start, NULL);
          misses += table->Search(u[i]);
          gettimeofday(&it_end, NULL);
          diff = (double)(it_end.tv_sec - it_start.tv_sec) + (it_end.tv_usec - it_start.tv_usec)/1000000.0;
          if(diff > max) {
            max = diff;
          }
          if(diff < min) {
            min = diff;
          }
          stdev += diff*diff;
        }
        gettimeofday(&end, NULL);
        stdev /= n/2;
        stdev = sqrt(stdev);
        times << "Standard deviation: " << stdev << endl;
        times << "Maximum: " << max << endl;
        times << "Minimum: " << min << endl;
        times << "Accumulative time: ";
        diff = (double)(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
        times << diff << endl;
        times << "Average time: " << diff/(ten_5) << endl;
        times << "Averages misses: " << misses/(ten_5) << endl;
        times << "***********************************************************************" << endl;

        times << "Cluster lengths of the hash table" << endl;
        table->clusterRunLengths(clusterLengths);
        for(int i = 0; i < size; i++) {
          if(clusterLengths[i] != 0) {
            times << "Cluster size " << i+1 << ": " << clusterLengths[i] << endl;
          }
        }

        times << "\n\n\n";
        for(int i = 0; i < size; i++) {
          clusterLengths[i] = 0;
        }
      }
    //Free space
    delete[] s;
    delete[] u;
    delete[] d;
  }
  times.close();
  return 1;
}
