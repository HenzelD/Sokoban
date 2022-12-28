#ifndef TARGET_H
#define TARGET_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Target : GameObject {
public:
	Target(int gameMode);
	void display(RenderWindow &renderWindow);
	Position getPosition();
	void setPosition(Position position);
	void setTexture(Texture& texture);
};

#endif // TARGET_H