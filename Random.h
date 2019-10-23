/*
 * Random.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Valen Yamamoto
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <vector>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

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

template <typename U>
vector<U> weightedRandom(vector<U> values, vector<int> weights, int num) {
	vector<U> choices;

	for(int i = 0; i < num; i++) {
		choices.push_back(weightedRandom(values, weights));
	}

	return choices;
}

template <typename T>
void printVector(vector<T> v) {
	for(unsigned int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

template <typename T>
void print2DVector(vector<T> v) {
	for(unsigned int i = 0; i < v.size(); i++) {
		printVector(v[i]);
	}
	cout << endl;
}

#endif /* RANDOM_H_ */
