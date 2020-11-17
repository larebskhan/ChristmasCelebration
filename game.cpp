/*
Programmer Names: Lareb Khan and Allison Scott
Date of Completion: November 13th, 2020
Class Description: Implements all of the member variables and functions protoyped in the game header file. As mentioned in the header file, this class inherits from the world class and includes 2 other classes that interact during the simulation. The runGame funtion calls the rest of the functions in order to make the simulation run as intended.
Additional Comments: Overloaded operators are called in the talk function. We display the convincing levels of the players on the grid (to better understand what is causing switches) if you wish to see only the characters, you may uncomment line 36 and comment line 37 - 46 (however, the grid lines will not fall in line with how the grid should look).
*/

#include "game.h"
#include "person.h"
#include "festive.h"
#include <ctime>
#include <iostream>

using namespace std;

const int maxConvincingLevel = 25;
const int minConvincingLevel = -25;

const int boardSpaces = 100;

//Default Constructor for the Game
Game:: Game()
{
	day = 0;
	initGrid();
}
//Prints the flags of the people in the grid. X indicates Dummy, N indicates November and D indicates December
void Game::PrintGrid()
{
	UpdateGrid();
	cout << "-----------------------------------------------------------------------" << endl;
	for(int i = 0; i < 10; i ++)
	{
		for(int j = 0; j < 10; j++)
		{
            //cout << "|" << " " << grid[i][j] << " ";
	    if(festivePerson[i][j].getConvincingLevel() < 0 && festivePerson[i][j].getConvincingLevel() > -10)
          	  cout << "|" << " " << grid[i][j] << "  " << festivePerson[i][j].getConvincingLevel();
	    else if(festivePerson[i][j].getConvincingLevel() > 0 && festivePerson[i][j].getConvincingLevel() < 10)
		    cout << "|" << " " << grid[i][j] << "   " << festivePerson[i][j].getConvincingLevel();
	    else if(festivePerson[i][j].getConvincingLevel() < -9)
		    cout << "|" << " " << grid[i][j] << " " << festivePerson[i][j].getConvincingLevel();
	    else if(festivePerson[i][j].getConvincingLevel() > 9)
		    cout << "|" << " " << grid[i][j] << "  " << festivePerson[i][j].getConvincingLevel();
	    else
		    cout << "|" << " " << grid[i][j] << "   " << festivePerson[i][j].getConvincingLevel();
		}
		cout << "|" << endl;
		cout << "-----------------------------------------------------------------------" << endl;
	}
}
//Updates the grid to ensure that all of the flags assigned to the grid array correspond with the attributes of the people that hold that space.
void Game::UpdateGrid()
{
	int level = 0;
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j ++)
        {
            if(festivePerson[i][j].getFlag() != '\0')
            {
                grid[i][j] = festivePerson[i][j].getFlag();
            }
            if(dummyPerson[i][j].getFlag() != '\0')
            {
                grid[i][j] = dummyPerson[i][j].getFlag();
            }
        }
    }
}
//Initializes the grid by determining random x and y coordinates for the inital December and November players and populating the rest of the grid with dummy people
void Game::initGrid()
{
    //Sets everything to empty values
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			grid[j][i] = ' ';
			festivePerson[i][j].setFlag('\0');
			dummyPerson[i][j].setFlag('\0');
		}
	}
    //Generating Random values for the December and November x and y coordinates
	int NovemberX = rand() % 10; //rand number 0-9
	int NovemberY = rand() % 10; //rand number 0-9
	int DecemberX = rand() % 10; //rand number 0-9
	int DecemberY = rand() % 10; //rand number 0-9
	bool done = true;
	while(done)
	{
		if(NovemberX == DecemberX && NovemberY == DecemberY)
		{
			//If the Nov and Dec chairs start in the same spot, we randomize the Dec values again
			DecemberX = rand() % 10;
			DecemberY = rand() % 10;
		}
		else //Run until they are in different spots
		{
			done = false;
		}
	}
    //update the festing people with the new x and y coordinates, the flag, and the base convincing levels
	updateFestive(NovemberX, NovemberY, 'N', minConvincingLevel);
	updateFestive(DecemberX, DecemberY, 'D', maxConvincingLevel);
    
    //set the rest of the coordinates to dummy
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(grid[i][j] != 'N' && grid[i][j] != 'D')
			{
				updateDummy(i, j, 'X', 0); //starts with a convincing level of 0
			}
		}
	}
}
//Updates all of the important Festive class member variables based on passed in parameters
void Game::updateFestive(int x, int y, char flag, int level)
{
	festivePerson[x][y].setX(x);
	festivePerson[x][y].setY(y);
	festivePerson[x][y].setFlag(flag);
	festivePerson[x][y].setConvincingLevel(level);
	grid[x][y] = festivePerson[x][y].getFlag();
}
//Updates all of the important Person class member variables based on passed in parameters
void Game::updateDummy(int x, int y, char flag, int level)
{
	dummyPerson[x][y].setX(x);
	dummyPerson[x][y].setY(y);
	dummyPerson[x][y].setFlag(flag);
	dummyPerson[x][y].setConvincingLevel(level);
	grid[x][y] = dummyPerson[x][y].getFlag();
}
//Checks to make sure that the x and y coordinates are in bounds. Return true if in bounds, returns false if out of bounds
bool Game::checkBounds(int x, int y)
{
    if(x < 10 && x > -1 && y < 10 && y > -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//Returns a random dice number from 1-4 that will (in the talk function) correspond to up, right, down, and left
int Game::dice()
{
	int randMove = rand() % 4 + 1; //finds value 1-4
	return randMove;
}
/*Takes in whose turn it is to talk. Finds all of the same type of person, generates a random move (using the dice), and makes them all talk to the x and y coordinate that corresponds with the move.
 Conditions:
    1. Talking to the same type of person -> do nothing (checks this using an overloaded == operator)
    2. Talking to a dummy person -> they are converted to the same flag as you but with a convincing level that is 1 value less strong that yours (calls on the convert function)
        *Strongest value for December is 25, Weakest value for December is 1; Strongest value for November is -25, Weakest value for November is -1
    3. Talking to the opposite type of person -> sum the convincing levels of the two people and both will be converted based on the convinving level (neg = Nov, pos = Dec, 0 = Dummy)
 */
void Game::talk(char turn)
{
    int move = dice();//find the dice move
    int playerCoordinates[10][10];
    
    //Find all of the people with the same flag as the turn
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            playerCoordinates[i][j] = -1;
            if(festivePerson[i][j].getFlag() == turn)
            {
                playerCoordinates[i][j] = 1;
            }
        }
    }
    
    //Initialize variables to be used later
    int talkingX = 0;
    int talkingY = 0;
    int y1 = 0;
    int x1 = 0;
    char flag = '\0';
    int level = 0;
    
    if(move == 1)
    {
        //Move = 1 will move the players up on the grid
        cout << turn << " WILL MOVE UP" << endl;
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(playerCoordinates[i][j] == 1)//For every person with the same turn
                {
                    //set the coordinates of the person talking and the person being talked to
                    talkingX = i;
                    talkingY = j;
                    x1 = i-1;
                    y1 = j;
                    if(checkBounds(x1, y1) == true)//If the person being talked to is in bounds
                    {
                        if(festivePerson[x1][y1].getFlag() != '\0')//If the person being talked to is a festive person
                        {
                            if(festivePerson[talkingX][talkingY] == festivePerson[x1][y1])//OVERLOADED OPERATOR: If the two festive people are of the same type, then do nothing
                            {
                                
                            }
                            else//if the two festive people are different types
                            {
                                festivePerson[talkingX][talkingY] + festivePerson[x1][y1];//OVERLOADED OPERATOR: Sum their convincing levels
                                if(festivePerson[talkingX][talkingY].getConvincingLevel() > 0)//If the sum is greater than 0
                                {
                                    //convert both to December people with the updated convincing levels
                                    updateFestive(talkingX, talkingY, 'D', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateFestive(x1, y1, 'D', festivePerson[x1][y1].getConvincingLevel());
                                }
                                else if(festivePerson[talkingX][talkingY].getConvincingLevel() < 0)//If the sum is less than 0
                                {
                                    //convert both to November people with the updated convincing levels
                                    updateFestive(talkingX, talkingY, 'N', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateFestive(x1, y1, 'N', festivePerson[x1][y1].getConvincingLevel());
                                }
                                else//If the sum is equal to 0
                                {
                                    //convert both to Dummy people in the festive class and the dummy class
                                    updateFestive(talkingX, talkingY, '\0', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateDummy(talkingX, talkingY, 'X', 0);
                                    updateFestive(x1, y1, '\0', festivePerson[x1][y1].getConvincingLevel());
                                    updateDummy(x1, y1, 'X', 0);
                                }
                            }
                        }
                        else
                        {
                            //Converting a dummy
                            flag = festivePerson[talkingX][talkingY].getFlag();
                            if(flag == 'N')//If the person talking has a november flag
                            {
                                //increment the level (makes it less strong)
                                level = festivePerson[talkingX][talkingY].getConvincingLevel() + 1;
                            }
                            else if(flag == 'D')//If the person talking has a december flag
                            {
                                //decrement the level (makes it less strong)
                                level = festivePerson[talkingX][talkingY].getConvincingLevel() -1;
                            }
                            //call the convert function on the person being talked to, to convert them from a dummy to a festive person
                            convert(x1, y1, flag, level);
                        }
                    }
                }
            }
        }
    }
    //Same logic as move 1 follows for moves 2 - 4
    else if(move == 2)
    {
        cout << turn << " WILL MOVE RIGHT" << endl;
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(playerCoordinates[i][j] == 1)
                {
                    talkingX = i;
                    talkingY = j;
                    x1 = i;
                    y1 = j+1;
                    if(checkBounds(x1, y1) == true)
                    {
                        if(festivePerson[x1][y1].getFlag() != '\0')
                        {
                            if(festivePerson[talkingX][talkingY] == festivePerson[x1][y1])
                            {
                                
                            }
                            else
                            {
                                festivePerson[talkingX][talkingY] + festivePerson[x1][y1];
                                if(festivePerson[talkingX][talkingY].getConvincingLevel() > 0)
                                {
                                    updateFestive(talkingX, talkingY, 'D', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateFestive(x1, y1, 'D', festivePerson[x1][y1].getConvincingLevel());
                                }
                                else if(festivePerson[talkingX][talkingY].getConvincingLevel() < 0)
                                {
                                    updateFestive(talkingX, talkingY, 'N', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateFestive(x1, y1, 'N', festivePerson[x1][y1].getConvincingLevel());
                                }
                                else
                                {
                                    updateFestive(talkingX, talkingY, '\0', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateDummy(talkingX, talkingY, 'X', 0);
                                    updateFestive(x1, y1, '\0', festivePerson[x1][y1].getConvincingLevel());
                                    updateDummy(x1, y1, 'X', 0);
                                }
                            }
                        }
                        else
                        {
                            flag = festivePerson[talkingX][talkingY].getFlag();
                            if(flag == 'N')
                            {
                                level = festivePerson[talkingX][talkingY].getConvincingLevel() + 1;
                            }
                            else if(flag == 'D')
                            {
                                level = festivePerson[talkingX][talkingY].getConvincingLevel() -1;
                            }
                            convert(x1, y1, flag, level);
                        }
                    }
                }
            }
        }
    }
    else if(move == 3)
    {
        cout << turn << " WILL MOVE DOWN" << endl;
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(playerCoordinates[i][j] == 1)
                {
                    talkingX = i;
                    talkingY = j;
                    x1 = i+1;
                    y1 = j;
                    if(checkBounds(x1, y1) == true)
                    {
                        if(festivePerson[x1][y1].getFlag() != '\0')
                        {
                            if(festivePerson[talkingX][talkingY] == festivePerson[x1][y1])
                            {
                                
                            }
                            else
                            {
                                festivePerson[talkingX][talkingY] + festivePerson[x1][y1];
                                if(festivePerson[talkingX][talkingY].getConvincingLevel() > 0)
                                {
                                    updateFestive(talkingX, talkingY, 'D', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateFestive(x1, y1, 'D', festivePerson[x1][y1].getConvincingLevel());
                                }
                                else if(festivePerson[talkingX][talkingY].getConvincingLevel() < 0)
                                {
                                    updateFestive(talkingX, talkingY, 'N', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateFestive(x1, y1, 'N', festivePerson[x1][y1].getConvincingLevel());
                                }
                                else
                                {
                                    updateFestive(talkingX, talkingY, '\0', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateDummy(talkingX, talkingY, 'X', 0);
                                    updateFestive(x1, y1, '\0', festivePerson[x1][y1].getConvincingLevel());
                                    updateDummy(x1, y1, 'X', 0);
                                }
                            }
                        }
                        else
                        {
                            flag = festivePerson[talkingX][talkingY].getFlag();
                            if(flag == 'N')
                            {
                                level = festivePerson[talkingX][talkingY].getConvincingLevel() + 1;
                            }
                            else if(flag == 'D')
                            {
                                level = festivePerson[talkingX][talkingY].getConvincingLevel() -1;
                            }
                            convert(x1, y1, flag, level);
                        }
                    }
                }
            }
        }
    }
    else if(move == 4)
    {
        cout << turn << " WILL MOVE LEFT" << endl;
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(playerCoordinates[i][j] == 1)
                {
                    talkingX = i;
                    talkingY = j;
                    x1 = i;
                    y1 = j-1;
                    if(checkBounds(x1, y1) == true)
                    {
                        if(festivePerson[x1][y1].getFlag() != '\0')
                        {
                            if(festivePerson[talkingX][talkingY] == festivePerson[x1][y1])
                            {
                                
                            }
                            else
                            {
                                festivePerson[talkingX][talkingY] + festivePerson[x1][y1];
                                if(festivePerson[talkingX][talkingY].getConvincingLevel() > 0)
                                {
                                    updateFestive(talkingX, talkingY, 'D', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateFestive(x1, y1, 'D', festivePerson[x1][y1].getConvincingLevel());
                                }
                                else if(festivePerson[talkingX][talkingY].getConvincingLevel() < 0)
                                {
                                    updateFestive(talkingX, talkingY, 'N', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateFestive(x1, y1, 'N', festivePerson[x1][y1].getConvincingLevel());
                                }
                                else
                                {
                                    updateFestive(talkingX, talkingY, '\0', festivePerson[talkingX][talkingY].getConvincingLevel());
                                    updateDummy(talkingX, talkingY, 'X', 0);
                                    updateFestive(x1, y1, '\0', festivePerson[x1][y1].getConvincingLevel());
                                    updateDummy(x1, y1, 'X', 0);
                                }
                            }
                        }
                        else
                        {
                            flag = festivePerson[talkingX][talkingY].getFlag();
                            if(flag == 'N')
                            {
                                level = festivePerson[talkingX][talkingY].getConvincingLevel() + 1;
                            }
                            else if(flag == 'D')
                            {
                                level = festivePerson[talkingX][talkingY].getConvincingLevel() -1;
                            }
                            convert(x1, y1, flag, level);
                        }
                    }
                }
            }
        }
    }
}
//Takes in an x and y value, a flag, and a convincing level and converts a dummy person
void Game::convert(int x1, int y1, char flag, int level)
{
    //reflects conversion in dummy array and festive array
	updateDummy(x1,y1,'\0',0);
	updateFestive(x1,y1,flag,level);
}
//Runs the simulation. Function that is called in the main.
void Game::runGame()
{
    
    string gamePlay;
	bool done = false;
    char turn = 'D';
    //While loop runs until a stopping condition is met
    while (!done)
    {
        //Increment Day
        day++;
	    
        //Output to user
	    if(day == 1)
        {
            cout << "Would you like to see the first day? (y or n)" << endl;
            cin >> gamePlay;
        }
        else
        {
            cout << "Would you like to see the next day? (y or n)" << endl;
            cin >> gamePlay;
        }
	    
        if(gamePlay == "n")
        {
            done = true;
            break;
        }
        else if(gamePlay == "y")
        {
            cout << "November " << day << endl;
            PrintGrid();//print the grid
        }
        else
        {
            cout << "Invalid Input" << endl;
            exit(1);
        }
        bool canMove = false;
        
        //determine whose turn it is to talk
        if(turn == 'D')
        {
            turn = 'N';
            cout << "It will be November's turn to talk" << endl;
        }
        else if(turn == 'N')
        {
            turn = 'D';
            cout << "It will be December's turn to talk" << endl;
        }
        
        //Call the talk function
        talk(turn);
        
        //Stopping Conditions (1) Everyone is either november or december (2) there are still dummys on the board but all of one type of person have been converted (3) the month of november is over
        //Implement Stopping Condition 1
        int decCount = 0;
        int novCount = 0;
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(grid[i][j] == 'D')
                {
                    novCount = 0;
                    decCount++;
                }
                else if(grid[i][j] == 'N')
                {
                    decCount = 0;
                    novCount++;
                }
                else
                {
                    decCount = 0;
                    novCount = 0;
                }
                if(decCount == 100 || novCount == 100)
                {
                    done = true;
                    if(decCount == 100 || novCount == 0)
                    {
                        PrintGrid();
                        cout << "December Christmas Celebrators have won!" << endl;
                    	done = true;
                        break;
                    }
                    else if(novCount == 100 || decCount == 0)
                    {
                        PrintGrid();
                        cout << "November Christmas Celebrators have won!" << endl;
                        done = true;
                        break;
                    }
                }
            }
        }
        //Implement Stopping Condition 3
        if(day == 31)
        {
            done = true;
            cout << "The month of November is over. I guess we will celebrate Christmas in December!" << endl;
        }
        
        //Implement Stopping Condition 2
        decCount = 0;
        novCount = 0;
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(grid[i][j] == 'N')
                {
                    novCount++;
                }
                else if(grid[i][j] == 'D')
                {
                    decCount++;
                }
            }
        }
        if(decCount == 0)
        {
            PrintGrid();
            cout << "There are no more December players left to argue their case, so we will celebrate Christmas now!" << endl;
            done = true;
        }
        else if(novCount == 0)
        {
            PrintGrid();
            cout << "There are no more November players left to argue their case, so we will celebrate Christmas now!" << endl;
            done = true;
        }
    }
}
