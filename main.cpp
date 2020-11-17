/*
 Programmer Names: Lareb Khan and Allison Scott
 Date of Completion: November 13th, 2020
 Class Description: Creates an instance of a game class that simulates "November" and "December" people trying to convince the entire game board to celebrate Christmas in November and December, respectively. The main calls on the Game class's runGame function which takes care of all of the functionality of the game.
 Additional Comments: None
 */

#include <cstdlib>
#include <iostream>
#include "World.h"
#include "game.h"
#include "festive.h"

using namespace std; 

int main(int argc, char** argv)
{
    srand(time(0));//set the time: needed for randomizing values
    //create an instance of the game class and run the simulation
    Game gameSimulation;
    gameSimulation.runGame();
    
    return 0;
}
