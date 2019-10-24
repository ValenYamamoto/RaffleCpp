# RaffleCpp
A rewrite of raffle program in C++ as a practice. Takes in a csv file of names and number of tickets per prize and then takes a weighted random number selection to find winners.

## Reading from the file
Reading from the csv file is accomplished using the ifstream object and passing in the address of the file. 
```
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
```
Each row containing a entry for a person is then put into a custom struct called entry to hold the person's name and their entries for each prizes as a vector.
```
struct entry {
	string name;
	vector<int> tickets;
};
```
All the entries are kept together in a vector

## Operations to find winners
Once the file is read and the list of entrants is compiled, winners are then randomly selected, weighted by the number of tickets they have for each prize. 

```
template <typename T>
T weightedRandom(vector<T> values, vector<int> weights) {
	int sumWeights = accumulate(weights.begin(), weights.end(), 0);

	int random = rand() % sumWeights;

//	cout << "random " << random << endl;
//	cout << "sumWeights " << sumWeights << endl;

	for(unsigned int i = 0; i < weights.size(); i++) {
		random -= weights[i];

		if(random <= 0) {
			return values[i];
		}
	}

	return values[0];
}
```
```
vector<std::string> Data::winnersForPrizeNoReplacement(std::string prize) {

	vector<std::string> winners;
	for(int i = 0; i < getPrizeCount(prize); i++) {
		vector<std::string> names = getNames();
		vector<int> weights = ticketsForPrize(prize);
		std::string winner = weightedRandom(names, weights);
		winners.push_back(winner);
		vector<std::string>::iterator iterator = find(names.begin(), names.end(), winner);

		int index = distance(names.begin(), iterator);
		entries.erase(entries.begin() + index);
	}

	return winners;
}
```
The prizes are chosen left to right, and once a person wins, they are removed from any future drawings for prizes down the line.

## Displaying winners and outputing winners to file
After winers are selected, they are printed to the console as well as stored in an additional file.
Output is done is an fstream object.
```
void Data::displayWinners() {
	vector<std::string> prizes = getPrizes();
	vector<vector<std::string>> winners = getAllWinners();
	for(unsigned int i = 0; i <  prizes.size(); i++) {
		cout << prizes[i] << endl;
		printVector(winners[i]);
		cout << endl << endl;
	}
	writeWinnersToFile(winners);
}

void Data::writeWinnersToFile(vector<vector<std::string>> winners) {
	fstream outfile ("RaffleResults.txt", ios::out);
	for(unsigned int i = 0; i <  prizes.size(); i++) {
		outfile << prizes[i] << "\n";
		for(unsigned int j = 0; j < winners[i].size(); j ++) {
			outfile << winners[i][j] << " ";
		}
		outfile << "\n" << "\n";
	}
	outfile.close();
}
```
