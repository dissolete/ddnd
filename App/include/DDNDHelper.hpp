/**
* @file DDNDHelper.hpp
* @author Gage Thomas
*/

#ifndef DDNDHELPER_HPP
#define DDNDHELPER_HPP

#include "CRStatManager.hpp"
#include <ifstream>
#include <iostream>
#include <string>
#include <vector>

stuct person{

	std::string name;
	int maxHP;
	int currHP;
	int maxShields;
	int currShields;

	unsigned int kills;
	unsigned int damageDone;
	unsigned int damageTaken;
};

/**
* Reads the statistics for either player characters or enemy characters from
* a passed input file
* input file is structured like so: an int representing the number of people to read in
* followed by that number of instances of this pattern:
* string for a name, int for maxHP, int for maxShields, unsigned int for kills, unsigned
* int for damage done, unsigned int for damage taken, new line character.
* @param[in] a string representing the filename to read in
* @param[in] a vector of person structs to store the people in, passed by reference
*/
void read_in_stats(const std::string &filename, vector<person> &people){

	std::ifstream fin;
	fin.open(filename);

	int numPeople;
	fin >> numPeople;

	for(int i = 0; i < numPeople; i++){

		person individual;
		fin >> individual.name;
		fin >> individual.maxHP;
		individual.currHP = individual.maxHP;///sets current HP
		fin >> individual.maxShields;
		individual.currShields = individual.maxShields;///Sets current shields
		fin >> kills;
		fin >> damageDone;
		fin >> damageTaken;

		people.push_back(individual);

	}

	fin.close();
}

/**
* The reverse process of the read_in_stats function
*/
void output_stats(const std::string &filename, const vector<person> &people){

	std::ofstream fout;
	fout.open(filename);

	fout << people.size();///Outputs the number of people

	///Outputs each individual person
	for(int i = 0; i < people.size(); i++){

		person temp = people[i];
		fout << temp.name;
		fout << temp.maxHP;
		fout << temp.maxShields;
		fout << temp.kills;
		fout << temp.damageDone;
		fout << temp.damageTaken;
	}

	fout.close();
}

#endif