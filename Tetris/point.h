#pragma once

class Point
{
	int x, y;
public:
	void init(int x, int y);
	void draw(char ch, int color);
	void move(int x, int y);
	int getX();
	int getY();

};

