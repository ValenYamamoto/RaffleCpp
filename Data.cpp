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
	for(unsigned int i = 4; i < row.size(); i++) {
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
			for(unsigned int i = 4; i < row.size(); i++) {
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

