#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Position {
private:
	int x;
	int y;
public:
	Position();
	Position(int x, int y);
	Vector2f toVector2f(int gameMode);
	bool operator==(Position compareTo);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
};

#endif // POSITION_H