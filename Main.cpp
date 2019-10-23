/*
 * Main.cpp
 *
 *  Created on: Oct 22, 2019
 *      Author: Valen Yamamoto
 */
#include <iostream>
#include "Data.h"
#include "Random.h"


using namespace std;
int main() {
	std::string fileLoc = "RaffleData.csv";
	Data data(fileLoc);

//	vector<int> val = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//	vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//
//	printVector(weightedRandom(val, weights, 9));

	cout << endl << endl << endl << "PRINTING" << endl;
	printVector(data.winnersForPrize("Apple Airpods 2"));


}


