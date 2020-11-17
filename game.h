/*
Programmer Names: Lareb Khan and Allison Scott
Date of Completion: November 13th, 2020
Class Description: Header file for the game class. Inherits from a world class and implements functionality relating to the board grid. Also includes game functionality that is all called in the runGame function to allow for the entire simulation to run. Also creates instances of two other classes: Festive and Person (which are the two objects interacting in the simulation.
Additional Comments: None
*/
#ifndef GAME_H
#define GAME_H
#include <cstdlib>
#include "World.h"
#include "person.h"
#include "festive.h"

using namespace std;

class Game : World
{
	public: 
        Game();
		void PrintGrid();
 		void UpdateGrid();
        void initGrid();
        
		//Interaction Functionality
		int dice();
        void talk(char);
        void convert(int, int, char, int);
		void runGame();
		void updateFestive(int, int, char, int);
		void updateDummy(int, int, char, int);
        void daysGone();
	private:
		Festive festivePerson[10][10];
        Person dummyPerson[10][10];
        bool checkBounds(int, int);
};

#endif /* GAME_H */
