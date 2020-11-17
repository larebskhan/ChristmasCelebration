/*
Programmer Names: Lareb Khan and Allison Scott
Date of Completion: November 13th, 2020
Class Description: Header file for the fesitve class. This class is used in the game class as the festive person (inludes nov and dec people). The dummy person has x, y, flag, convincing level, and day member variables and then also has getters and setters for each variable. This class also overloads 3 operators. The + operator sums the convincing levels, the == operator checks to see if the flags of the two fesitve people are equal, and the = operator sets the flag and convincing level of the called object to the flag and convincing level of the calling object
Additional Comments: None
*/
#ifndef FESTIVE_H
#define FESTIVE_H
#include <cstdlib>

using namespace std;

class Festive
{
	public: 
		Festive();
		char getFlag();	
        int getX();
        int getY();
        int getConvincingLevel();
        int getDay();
		bool getIsChair();

        void setX(int);
        void setY(int);
        void setConvincingLevel(int);
        void setFlag(char);
        void setIsChair();
		void setDay(int);
    
        const Festive operator+(Festive&);
        bool operator==(Festive);
        Festive operator=(Festive);

	private:
		bool isChair;
		int x;
        int y;
        int convincingLevel;
        char flag;
        int day;
};

#endif /* FESTIVE_H */
