/*
Programmer Names: Lareb Khan and Allison Scott
Date of Completion: November 13th, 2020
Class Description: Header file for the person class. This class is used in the game class as the dummy person. The dummy person has x, y, flag, convincing level, and day member variables and then also has getters and setters for each variable.
Additional Comments: None
*/
#ifndef PERSON_H
#define PERSON_H
#include <cstdlib>

using namespace std;

class Person
{
	public: 
		Person();
                //~Person();
                char getFlag();	
                int getX();
                int getY();
                int getConvincingLevel();
                int getDay();	

                void setX(int);
                void setY(int);
                void setConvincingLevel(int);
                void setFlag(char);
                void setDay(int);

        private:
                int x;
                int y;
                int convincingLevel;
                char flag;
                int day;
};

#endif /* PERSON_H */
