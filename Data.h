/*
 * Data.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Valen Yamamoto
 */

#ifndef DATA_H_
#define DATA_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

struct entry {
	string name;
	vector<int> tickets;
};

class Data {
	ifstream file;
	string fileName;
	vector<struct entry> entries;
	vector<int> prizeNumbers;
	vector<std::string> prizes;
public:

	Data(string fileName);

	vector<struct entry> getEntries();

	vector<std::string> getNames();

	vector<std::string> getPrizes();

	int getPrizeCount(std::string prize);

	vector<int> ticketsForPrize(std::string prize);

	vector<std::string> winnersForPrizeReplacement(std::string prize);

	vector<std::string> winnersForPrizeNoReplacement(std::string prize);

	vector<vector<std::string>> getAllWinners();

	void displayWinners();

	void writeWinnersToFile(vector<vector<std::string>> winners);

private:

	void openFile();

	void closeFile();

	void readFromFile();
};



#endif /* DATA_H_ */
