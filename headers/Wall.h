#ifndef WALL_H
#define WALL_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Wall: GameObject {
public:
	Wall(int gameMode);
	void display(RenderWindow& renderWindow);
	Position getPosition();
	void setPosition(Position position);
	void setTexture(Texture& texture);
};

#endif // WALL_H