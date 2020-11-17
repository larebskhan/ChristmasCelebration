/*
Programmer Names: Lareb Khan and Allison Scott
Date of Completion: November 13th, 2020
Class Description: Implements all of the member functions prototyped in the festive header file.
Additional Comments: None
*/

#include "festive.h"

#include <iostream>
using namespace std;

const int maxConvincingLevel = 25;
const int minConvincingLevel = -25;

//Default constructor
Festive::Festive()
{
    x = 0;
    y = 0;
    convincingLevel = 0;
    flag = 'X';
    isChair = false;
    day = 0;
}

//Member variable getters
int Festive::getX()
{
    return x;
}
int Festive::getY()
{
    return y;
}
int Festive::getConvincingLevel()
{
    return convincingLevel;
}
char Festive::getFlag()
{
    return flag;
}
int Festive::getDay()
{
    return day;
}
bool Festive::getIsChair()
{
    return isChair;
}

//Member variable getters
void Festive::setDay(int _day)
{
    day = _day;
}
void Festive::setX(int _x)
{
    //Error ChecK: x value is not set out of bounds of the world class grid
    if(_x >= 0 && _x <= 9)
    {
        x = _x;
    }
}
void Festive::setY(int _y)
{
    //Error ChecK: y value is not set out of bounds of the world class grid
    if(_y >= 0 && _y <= 9)
    {
        y = _y;
    } 
}
void Festive::setConvincingLevel(int _convincingLevel)
{
    //set the convinving level as long as it is less strong than the chair's (which is the min and max levels)
    if(_convincingLevel <= maxConvincingLevel && _convincingLevel >= minConvincingLevel)
    {
        convincingLevel = _convincingLevel;
    }
    else
    {
        convincingLevel = 0;
    }
    
}
void Festive::setFlag(char _flag)
{
    //Set the flags
    if(_flag == 'D')
    {
        flag = 'D';
    }
    else if(_flag == 'N')
    {
        flag = 'N';
    }
    else
    {
        flag = '\0';
    }
}

void Festive::setIsChair()
{
    if(convincingLevel == maxConvincingLevel || convincingLevel == minConvincingLevel)
    {
        isChair = true;
    }
    else
    {
        isChair = false;
    }
}

//Operator Overloading
const Festive Festive::operator+(Festive& festiveIDK)
{
    //get the convincing level of the called object and the calling object and find the sum of the 2
    int level1 = festiveIDK.getConvincingLevel();
    int level2 = convincingLevel;
    int total = level1 + level2;
    
    //set the convincing levels of the called and calling object to the sum
    festiveIDK.setConvincingLevel(total);
    this->setConvincingLevel(total);
    
    //set the corresponding flags of the called and calling object to the sum
    if(total > 0)
    {
        this->setFlag('D');
        festiveIDK.setFlag('D');
    }
    else if(total < 0)
    {
        festiveIDK.setFlag('N');
        this->setFlag('N');
    }
    //return the calling object
    return *this;
}
bool Festive::operator==(Festive festiveIDK)
{
    //if the calling object's flag and the called object's flag are the same return true, otherwise return false
    if(flag == festiveIDK.getFlag())
    	return true;
    return false;
}
Festive Festive::operator=(Festive festiveIDK)
{
    //set the called object's convincing level to the calling objects convincing level
    int level = this->getConvincingLevel();
    festiveIDK.setConvincingLevel(level);
    
    //set the called object's flag to the calling objects flag
    char type = this->getFlag();
    festiveIDK.setFlag(flag);
    
    //return the calling object
    return *this;
}
