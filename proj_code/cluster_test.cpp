#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <sys/time.h>
#include "hashtable.h"

using namespace std;

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
  ofstream results, stats, misc, clusters;

  cout << "Allocating hash table" << endl;
  hashtable* table = new hashtable(two_20);
  cout << "Successfully allocated space" << endl;
  struct timeval start,end,it_start, it_end;	// time structure for starting and ending time 
  size = table->Size();
  clusterLengths = new int[size];

  misc.open("stats.txt");
  results.open("times.txt");
  stats.open("misses.txt");
  clusters.open("clusters.txt");

  for(int i = 0; i < 6; i++) {
    alpha = a[i];
    n = alpha*size;
    if(n % 2 != 0) {
      n--;
    }

    cout << "Generating " << n << " keys | Alpha = " << alpha << endl;
    results << "------------------------------------------------------------------" << endl;
    results << "ALPHA = " << alpha << endl;
    results << "------------------------------------------------------------------" << endl;

    stats << "------------------------------------------------------------------" << endl;
    stats << "ALPHA = " << alpha << endl;
    stats << "------------------------------------------------------------------" << endl;

    misc << "------------------------------------------------------------------" << endl;
    misc << "ALPHA = " << alpha << endl;
    misc << "------------------------------------------------------------------" << endl;

    clusters << "------------------------------------------------------------------" << endl;
    clusters << "ALPHA = " << alpha << endl;
    clusters << "------------------------------------------------------------------" << endl;
    
    //Use the same keys for each hash combination
   	s = new long long[n/2];
  	d = new long long[n/2];
	  u = new long long[ten_5];

    cout << "Generating " << n << " keys" << endl;
  	table->genKeys(s,d,u,n);
//    table->genNonRandom(n, 1, s, u, d);
    //Loop through possible primary and secondary hash combinations
    results << "Avg S prior\tAvg U prior\tAvg S post\tAvg U post" << endl;
    stats << "Avg S misses prior\tAvg U misses prior\tAvg S misses post\tAvg U misses post" << endl;

    for(int type = 1; type <= 2; type++) {
      for(int type2 = 1; type2 <= 3; type2++) {
        table->resetTable();
        cout << "Selecting hashes " << type << " and " << type2 << endl;
        table->selectHash(type, type2);
        results << "Runtimes for primary hash type " << type << " and secondary hash type " << type2 << endl;
        stats << "Avg additional probes for primary hash type " << type << " and secondary hash type " << type2 << endl;
        misc << "Stats for primary hash type " << type << " and secondary hash type " << type2 << endl;
        clusters << "Clusters for primary hash type " << type << " and secondary hash type " << type2 << endl;
        //Insert keys into hash table
        for(int i = 0; i < n/2; i++) {
          table->Insert(s[i]);
        }
        for(int i = 0; i < n/2; i++) {
          table->Insert(d[i]);
        }

        max = 0;
        min = 1;
        stdev = 0;
        misses = 0;
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
        //Accumulated and average times, standard dev, max, min, and average misses of this run
        diff = (double)(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
        results << diff/(n/2) << "\t";
        stats << misses/(n/2) << "\t";
        misc << "stdev: " << stdev << "\n" <<"max: " << max << "\n" << "min: " << min << endl;

        max = 0;
        min = 1;
        stdev = 0;
        misses = 0;
        cout << "Searching from U pre-deletion" << endl;
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
        stdev /= ten_5;
        stdev = sqrt(stdev);
        //standard dev, max, min, and average misses of this run
        diff = (double)(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
        results << diff/(ten_5) << "\t";
        stats << misses/(ten_5) << "\t";
        misc << "stdev: " << stdev << "\n" <<"max: " << max << "\n" << "min: " << min << endl;

        //Delete keys from the hash table
        for(int i = 0; i < n/2; i++) {
          table->Delete(d[i]);
        }

        max = 0;
        min = 1;
        stdev = 0;
        misses = 0;
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
        //standard dev, max, min, and average misses of this run
        diff = (double)(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
        results << diff/(n/2) << "\t";
        stats << misses/(n/2) << "\t";
        misc << "stdev: " << stdev << "\n" <<"max: " << max << "\n" << "min: " << min << endl;

        max = 0;
        min = 1;
        stdev = 0;
        misses = 0;
        cout << "Searching from U post-deletion" << endl;
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
        stdev /= ten_5;
        stdev = sqrt(stdev);
        //standard dev, max, min, and average misses of this run
        diff = (double)(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
        results << diff/(ten_5) << endl;
        stats << misses/(ten_5) << endl;
        misc << "stdev: " << stdev << "\n" <<"max: " << max << "\n" << "min: " << min << endl;

        table->clusterRunLengths(clusterLengths);
        for(int i = 0; i < size; i++) {
          if(clusterLengths[i] != 0) {
            clusters << i+1 << "\t" << clusterLengths[i] << endl;
          }
        }

        clusters << "\n";
        for(int i = 0; i < size; i++) {
          clusterLengths[i] = 0;
        }
      }
    }
    results << "\n";
    //Free space
    delete[] s;
    delete[] u;
    delete[] d;
  }
  results.close();
  clusters.close();
  return 1;
}
