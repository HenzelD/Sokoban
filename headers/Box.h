#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include <vector>

class Box : GameObject {
public:
	Box(int gameMode);
	void move(int direction); //1-right, 2-left, 3-up, 4-down
	bool canBeMoved(int direction, std::vector<Wall*> walls, std::vector<Position> boxesPositions);
	void display(RenderWindow& renderWindow);
	Position getPosition();
	void setPosition(Position position);
	void setTexture(Texture& texture);
};

#endif // BOX_H