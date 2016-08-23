/**
* @file DDNDHelper.hpp
* @author Gage Thomas
*/

#ifndef DDNDHELPER_HPP
#define DDNDHELPER_HPP

#include <fstream>
#include <string>
#include "CRGroup.hpp"
#include "CRMath.hpp"
#include <SFML/System/Vector2.hpp>

struct person{

	std::string name;
	int maxHP;
	int currHP;
	int maxShields;
	int currShields;

	unsigned int kills;
	unsigned int damageDone;
	unsigned int damageTaken;
};

const int PISTOL = 0;
const int RIFLE = 1;
const int MACHINE_GUN = 2;
const int SNIPER = 3;
const int SHOTGUN = 4;

const int SQUARE_WIDTH = 32;

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
void read_in_stats(const std::string &filename, CRE::Group<person> &people){

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
		fin >> individual.kills;
		fin >> individual.damageDone;
		fin >> individual.damageTaken;

		///Add the individual as a property to an entity in the passed group
		CRE::Entity *addition = new CRE::Entity(individual.name);
		addition -> _properties.add("Statistics", individual);
		people.add(addition);

	}

	fin.close();
}

/**
* The reverse process of the read_in_stats function
*/
void output_stats(const std::string &filename, const CRE::Group<person> &people){

	std::ofstream fout;
	fout.open(filename);

	fout << people.size();///Outputs the number of people

	///Outputs each individual person
	for(int i = 0; i < people.size(); i++){

		person temp = people[i];
		fout << temp.name << endl;
		fout << temp.maxHP << ' ';
		fout << temp.maxShields << ' ';
		fout << temp.kills << ' ';
		fout << temp.damageDone << ' ';
		fout << temp.damageTaken << endl;
	}

	fout.close();
}

int get_min_roll(sf::Vector2f person1, sf::Vector2f person2, int weaponCode){

	int rollCalc;

///Uses Distance formula to calculate distance in terms of squares, not pixels
	int distance = floor(sqrt(pow(person1.x - person2.x, 2) + pow(person1.y - person2.y, 2)) / SQUARE_WIDTH);

	switch(weaponCode){

		case RIFLE:///Rifle uses the same calculation as pistol

		case PISTOL:
		///Since Distance should always be at least 1, the real minimum roll is 5
			rollCalc = 5 + distance / 2;
			break;

		case MACHINE_GUN:

			rollCalc = 4 + distance;
			break;

		case SNIPER:

			///Short range calculation
			if(distance <= 5){
				rollCalc = 10 + (5 - distance);
			} else {///Long range calcs
				rollCalc = 7 + ((distance - 4) /  2);
			}
			break;

		case SHOTGUN:

			rollCalc = fmax(3, 3 * distance);
			break;
	}

	///rollCalc will never be 1, only need to check that it is <= 19
	return fmin(19, rollCalc);
}

#endif