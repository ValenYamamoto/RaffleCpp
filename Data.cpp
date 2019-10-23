/*
 * Data.cpp
 *
 *  Created on: Oct 21, 2019
 *      Author: Valen Yamamoto
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Data.h"
#include <algorithm>
#include "Random.h"
using namespace std;


Data::Data(string fileName) {
		cout << "in Constructor" << endl;
		this->fileName = fileName;
		openFile();
		readFromFile();
		closeFile();
}

vector<struct entry> Data::getEntries() {
	return entries;
}

vector<std::string> Data::getNames() {
	vector<std::string> names;
	for(struct entry e: entries) {
		names.push_back(e.name);
	}
	return names;
}

vector<std::string> Data::getPrizes() {
	return prizes;
}

int Data::getPrizeCount(std::string prize) {
	vector<std::string>::iterator iterator = find(prizes.begin(), prizes.end(), prize);

	int index = distance(prizes.begin(), iterator);

	return prizeNumbers[index];
}

vector<int> Data::ticketsForPrize(std::string prize) {
	vector<int> tickets;
	vector<std::string>::iterator iterator = find(prizes.begin(), prizes.end(), prize);

	int index = distance(prizes.begin(), iterator);

	for(struct entry x: entries) {
		tickets.push_back(x.tickets[index + 4]);
	}
	return tickets;
}

vector<std::string> Data::winnersForPrizeReplacement(std::string prize) {
	vector<int> weights = ticketsForPrize(prize);

	vector<std::string> winnerNames = weightedRandom(getNames(), weights, getPrizeCount(prize));

	return winnerNames;
}

vector<std::string> Data::winnersForPrizeNoReplacement(std::string prize) {

	vector<std::string> winners;
	for(int i = 0; i < getPrizeCount(prize); i++) {
		vector<std::string> names = getNames();
		vector<int> weights = ticketsForPrize(prize);
		std::string winner = weightedRandom(names, weights);
//		cout << winner << endl;
		winners.push_back(winner);
//		cout << "Here" << endl;
		vector<std::string>::iterator iterator = find(names.begin(), names.end(), winner);

		int index = distance(names.begin(), iterator);
//		cout << "index " << index << endl;
		entries.erase(entries.begin() + index);
	}

	return winners;
}

vector<vector<std::string>> Data::getAllWinners() {
	vector<vector<std::string>> allWinners;

	for(std::string prize : getPrizes()) {
		allWinners.push_back(winnersForPrizeNoReplacement(prize));
	}
	return allWinners;
}

void Data::displayWinners(vector<std::string> prizes, vector<vector<std::string>> winners) {
	for(unsigned int i = 0; i <  prizes.size(); i++) {
		cout << prizes[i] << endl;
		printVector(winners[i]);
		cout << endl << endl;
	}
}
void Data::openFile() {
	try {
		cout << "Opening File" << endl;
		file.open(fileName);
		cout << file.is_open();
		std::cout << " good()=" << file.good();
		std::cout << " eof()=" << file.eof();
		std::cout << " fail()=" << file.fail();
		std::cout << " bad()=" << file.bad();
	} catch(const ifstream::failure& e) {
		cout << "Exception opening/reading file";
		exit(1);
	}
}

void Data::closeFile() {
	try {
		cout << "Closing File" << endl;
		file.close();
	} catch(const ifstream::failure& e) {
		cout << "Exception closing file";
		exit(1);
	}
}

void Data::readFromFile() {
	std::string temp, line, word;
	cout << "Reading File" << endl;
	vector<string> row;

	//****************************** GET PRIZE #s
	getline(file, line);
	row.clear();

	stringstream s(line);

	while(std::getline(s, word, ',')) {
		if (word != "") {
			row.push_back(word);
		}
	}

	for(unsigned int i = 1; i < row.size(); i++) {
		prizeNumbers.push_back(stoi(row[i]));
	}

	cout << "PRIZE NUMBERS" << endl;
	for (int x : prizeNumbers) {
		cout << x << " ";
	}
	cout << endl;

	//****************************** GET COLUMN HEADERS
	getline(file, line);
	row.clear();

	stringstream ss(line);

	while(std::getline(ss, word, ',')) {
		if (word != "") {
			row.push_back(word);
		}
	}

	cout << "Row size" << row.size() << endl;
	for(unsigned int i = 4; i < row.size() - 1; i++) {
		prizes.push_back(row[i]);
	}
	cout << "PRIZES" << endl;
	for (std::string x : prizes) {
		cout << x << " ";
	}
	cout << endl;

	//***************************** GET DATA FOR ENTRIES
	while(getline(file, line)) {
		row.clear();

		stringstream s(line);

		while(std::getline(s, word, ',')) {
			if (word != "") {
				row.push_back(word);
			}
		}

//			cout << "PRINTING DATA" << endl;
//			for(std::string x: row) {
//				cout << x << " ";
//			}
//			cout << endl;

		if(row.size() > 0 && row[0] != " ") {
			std::string name = row[0];

			vector<int> ticketNumber;
			for(unsigned int i = 4; i < row.size() - 1; i++) {
				ticketNumber.push_back(stoi(row[i]));
			}

			struct entry person = {name, ticketNumber};

			entries.push_back(person);
		}
	}

	for(struct entry e: entries) {
		cout << e.name << endl;
	}

}


//int main() {
//	std::string fileLoc = "RaffleData.csv";
//	Data data(fileLoc);
//}

