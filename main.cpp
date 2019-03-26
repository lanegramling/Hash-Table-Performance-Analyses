#include <iostream>   //I/O
#include <iomanip>    //I/O formatting convenience
#include <fstream>    //File Input handling
#include <string>     //String convenience
#include <stdlib.h>   //srand, rand
#include <time.h>     //time

#include "Timer.h"                  //Provided Timer Class
#include "Hash.h"	                  //Hash with chaining
#include "HashDouble.h"	              //Hash with double hashing
#include "HashQuadraticProbing.h"	  //Hash with quadratic probing

//Load a Hash from a (.txt) file - (DEBUG)
Hash<int> loadHash(std::string fName, int tableSize) {
  std::ifstream file(fName);
  int num;
  std::cout << "\n\nAttempting to create an open hash table with chaining from file " << fName << "...";
  if (file.is_open()) {
    Hash<int>* hash = new Hash<int>(tableSize);
    while(file >> num) hash->insert(num); //Load numbers to table.
    file.close();
    return *hash;
  }
  else {
      std::cout << "\nError: File could not be opened. Preparing empty table with size " << tableSize;
      Hash<int>* hash = new Hash<int>(tableSize);
      return *hash;
  }
}

//Load a HashDouble from a (.txt) file - (DEBUG)
HashDouble<int> loadHashDouble(std::string fName, int tableSize) {
  std::ifstream file(fName);
  int num;
  std::cout << "\nAttempting to create a double hash table from file " << fName << "...";
  if (file.is_open()) {
    HashDouble<int>* hash = new HashDouble<int>(tableSize); //Size 53 is assumed in this implementation
    while(file >> num) hash->insert(num); //Load numbers to table.
    file.close();
    return *hash;
  }
  else return HashDouble<int>(0);
}

//Load a HashQuadraticProbing from a (.txt) file - (DEBUG)
HashQuadraticProbing<int> loadHashQuadraticProbing(std::string fName, int tableSize) {
  std::ifstream file(fName);
  int num;
  std::cout << "\nAttempting to create hash table with  quadratic probing from file " << fName << "...";
  if (file.is_open()) {
    HashQuadraticProbing<int>* hash = new HashQuadraticProbing<int>(tableSize); //Size 53 is assumed in this implementation
    while(file >> num) hash->insert(num); //Load numbers to table.
    file.close();
    return *hash;
  }
  else return HashQuadraticProbing<int>(0);
}

//Main function
int main(int argc, char* argv[])
{

    //Main IO loop - controls interaction with both Double and Quadratically Probed Hash tables.
	int choice = 0;
	do {
        std::cout << "\n\n................................................................"
    									<< "\nPlease choose one of the following commands:"
    									<< "\n1- Test Hash Tables"
    									<< "\n2- Performance Comparison"
    									<< "\n3- Exit"
    									<< "\n> ";
        std::cin >> choice;
    	int num = 0; //Contains I/O responses
        if (choice == 1) {   //Test Hash Tables
            std::cout << "\nWhat is the table size?\n> ";
            std::cin >> num;

            std::cout << "\n\n................................................................"
                      << "\nTesting hash tables using:\nInput file: data.txt\nM = " << num << "\nP = 5\nK = 4";

            //Load hash tables - K=4 and P=5 are gven as default parameters because test is assumed to have size M=11.
            Hash<int> hashC = loadHash("data.txt", num);
            HashQuadraticProbing<int> hashQP = loadHashQuadraticProbing("data.txt", num);
            HashDouble<int> hashD = loadHashDouble("data.txt", num);

            hashC.print();
            hashQP.print();
            hashD.print();
        } else if (choice == 2) { //Performance Comparison
            int M = 1000003;
            int K = 997;
            int P = 20;
            std::cout << "\n\n................................................................"
                      << "\nGenerating performance analysis with randomized test data using:"
                      << "\nM = " << M << "\nP = " << P << "\nK = " << K;

            //Table & Timer instantiation
            Hash<int>* hashC = new Hash<int>(M);
            HashQuadraticProbing<int>* hashQP = new HashQuadraticProbing<int>(M, K);
            HashDouble<int>* hashD = new HashDouble<int>(M, K, P);
            Timer t;

            //Output data holders
            double buildTimes[5] = {0, 0, 0, 0, 0};
            double foundTimes[5] = {0, 0, 0, 0, 0};
            double notFoundTimes[5] = {0, 0, 0, 0, 0};

            //Generate performance analysis - OPEN HASHING
            std::cout << "\n\n-----------------------Performance - Open Hashing-----------------------";
            std::cout << "\n___________|  100,000  |  200,000  |  300,000  |  400,000  |  500,000  |";
            for(int loadScale = 1; loadScale <= 5; loadScale++){                           //Cycle through table sizes
                hashC->unload(); //Unload the hash table to be reused
                for (int run = 0; run < 5; run++) {                                                               //Refresh hash table for next pass
                    srand(time(NULL));                                                                  //(Re)Seed random generator
                    t.start();                                                                          //Timer start .
                    for (int i = 0; i < (((double)loadScale / 10) * M); i++) hashC->insert(rand() % (5 * M));   //Insertions  .
                    buildTimes[loadScale - 1] += t.stop();

                    bool found;
                    int foundNum = 0;
                    int notFoundNum = 0;
                    for (int i = 0; i < ((0.01) * M); i++) {                                            //Perform 0.01 * M number of searches
                        t.start();                                                                      //Timer start .
                        found = hashC->find(rand() % (5 * M));                                          //Searches    .
                        double ft = t.stop(); //Time to find (or not find)                              //Timer stop  . (+ capture duration)
                        if (found) foundTimes[loadScale - 1] += ft;                            //Accumulate found/notfound CPU times
                        else notFoundTimes[loadScale - 1] += ft;
                    }
                }
                for (int i = 0; i < 5; i++) {           //Average over 5 passes
                    buildTimes[i] /= 5;
                    foundTimes[i] /= 5;
                    notFoundTimes[i] /= 5;
                }
            }

            std::cout << "\nBuild      |";
            for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << buildTimes[i] << "s |";        //Output CPU time to cell
            std::cout << "\nFound      |";
            for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << foundTimes[i] << "s |";        //Output CPU time to cell
            std::cout << "\nNot Found  |";
            for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << notFoundTimes[i] << "s |";        //Output CPU time to cell

            //Generate performance analysis - HASHING WITH QUADRATIC PROBING
            std::cout << "\n\n-------------Performance - Hashing with Quadratic Probing---------------";
            std::cout << "\n___________|  100,000  |  200,000  |  300,000  |  400,000  |  500,000  |";
            for(int loadScale = 1; loadScale <= 5; loadScale++){                           //Cycle through table sizes
                hashQP->unload(); //Unload the hash table to be reused
                for (int run = 0; run < 5; run++) {                                                               //Refresh hash table for next pass
                    srand(time(NULL));                                                                  //(Re)Seed random generator
                    t.start();                                                                          //Timer start .
                    for (int i = 0; i < (((double)loadScale / 10) * M); i++) hashQP->insert(rand() % (5 * M));   //Insertions  .
                    buildTimes[loadScale - 1] += t.stop();

                    bool found;
                    int foundNum = 0;
                    int notFoundNum = 0;
                    for (int i = 0; i < ((0.01) * M); i++) {                                            //Perform 0.01 * M number of searches
                        t.start();                                                                      //Timer start .
                        found = hashQP->find(rand() % (5 * M));                                          //Searches    .
                        double ft = t.stop(); //Time to find (or not find)                              //Timer stop  . (+ capture duration)
                        if (found) foundTimes[loadScale - 1] += ft;                            //Accumulate found/notfound CPU times
                        else notFoundTimes[loadScale - 1] += ft;
                    }
                }
                for (int i = 0; i < 5; i++) {           //Average over 5 passes
                    buildTimes[i] /= 5;
                    foundTimes[i] /= 5;
                    notFoundTimes[i] /= 5;
                }
            }

            std::cout << "\nBuild      |";
            for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << buildTimes[i] << "s |";        //Output CPU time to cell
            std::cout << "\nFound      |";
            for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << foundTimes[i] << "s |";        //Output CPU time to cell
            std::cout << "\nNot Found  |";
            for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << notFoundTimes[i] << "s |";        //Output CPU time to cell


            //Generate performance analysis - HASHING WITH DOUBLE HASHING
            std::cout << "\n\n-----------Performance - Hashing with Double Hashing-------------------";
            std::cout << "\n___________|  100,000  |  200,000  |  300,000  |  400,000  |  500,000  |";
            for(int loadScale = 1; loadScale <= 5; loadScale++){                           //Cycle through table sizes
                hashD->unload(); //Unload the hash table to be reused
                for (int run = 0; run < 5; run++) {                                                               //Refresh hash table for next pass
                    srand(time(NULL));                                                                  //(Re)Seed random generator
                    t.start();                                                                          //Timer start .
                    for (int i = 0; i < (((double)loadScale / 10) * M); i++) hashD->insert(rand() % (5 * M));   //Insertions  .
                    buildTimes[loadScale - 1] += t.stop();

                    bool found;
                    int foundNum = 0;
                    int notFoundNum = 0;
                    for (int i = 0; i < ((0.01) * M); i++) {                                            //Perform 0.01 * M number of searches
                        t.start();                                                                      //Timer start .
                        found = hashD->find(rand() % (5 * M));                                          //Searches    .
                        double ft = t.stop(); //Time to find (or not find)                              //Timer stop  . (+ capture duration)
                        if (found) foundTimes[loadScale - 1] += ft;                            //Accumulate found/notfound CPU times
                        else notFoundTimes[loadScale - 1] += ft;
                    }
                }
                for (int i = 0; i < 5; i++) {           //Average over 5 passes
                    buildTimes[i] /= 5;
                    foundTimes[i] /= 5;
                    notFoundTimes[i] /= 5;
                }
            }

            std::cout << "\nBuild      |";
            for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << buildTimes[i] << "s |";        //Output CPU time to cell
            std::cout << "\nFound      |";
            for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << foundTimes[i] << "s |";        //Output CPU time to cell
            std::cout << "\nNot Found  |";
            for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << notFoundTimes[i] << "s |";        //Output CPU time to cell


            //Unload tables
            hashC->unload();
            hashQP->unload();
            hashD->unload();

        } else if (choice == 3) std::cout << "\n\nExiting - dumping tables...\n\n"; //Handle Exit
        else std::cout << "\nThat option was not found. Please try again.";       //Handle unrecognized input
    } while (choice != 3);
}
