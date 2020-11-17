/*
Programmer Names: Lareb Khan and Allison Scott
Date of Completion: November 13th, 2020
Class Description: Implements all of the member functions prototyped in the person header file.
Additional Comments: None
*/
#include "person.h"
#include <iostream>
using namespace std;

const int maxConvincingLevel = 25;
const int minConvincingLevel = -25;
//Default Constructor
Person::Person()
{
    x = 0;
    y = 0;
    convincingLevel = 0;
    flag = 'X';
    day = 0;
}
//Member Variable Getters
int Person::getX()
{
    return x;
}
int Person::getY()
{
    return y;
}
int Person::getConvincingLevel()
{
    return convincingLevel;
}
char Person::getFlag()
{
    return flag;
}
int Person::getDay()
{
    return day;
}

//Member Variable Setters
void Person::setDay(int _day)
{
    day = _day;
}
void Person::setX(int _x)
{
    //Error ChecK: x value is not set out of bounds of the world class grid
    if(_x >= 0 && _x <= 9)
    {
        x = _x;
    }
}
void Person::setY(int _y)
{
    //Error ChecK: y value is not set out of bounds of the world class grid
    if(_y >= 0 && _y <= 9)
    {
        y = _y;
    } 
}
void Person::setConvincingLevel(int _convincingLevel)
{
    //set the convinving level as long as it is less strong than the chair's (which is the min and max levels)
    if(_convincingLevel < maxConvincingLevel && _convincingLevel > minConvincingLevel)
    {
        convincingLevel = _convincingLevel;
    }
    else
    {
        convincingLevel = 0;
    }
    
}
void Person::setFlag(char _flag)
{
    //Set the flags
    if(_flag == 'X')
    {
        flag = _flag;
    }
    else
    {
        flag = '\0';
    }
}
