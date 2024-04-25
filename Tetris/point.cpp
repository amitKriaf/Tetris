#include "point.h"
#include "general.h"
#include <iostream>
#include <Windows.h>
using namespace std;

void Point::init(int x, int y)
{
	// This function initiate the point.
	this->x = x;
	this->y = y;
}

void Point::draw(char ch, int color)
{
	// This function draw the point.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	gotoxy(x, y);
	cout << ch;
}


void Point::move(int x, int y)
{
	// This funtion get (x,y) and adding it to the curr point.
	this->x += x;
	this->y += y;
}

int Point::getX()
{
	// This function return the value of the x.
	return x;
}

int Point::getY()
{
	// This function return the value of the y.
	return y;
}
