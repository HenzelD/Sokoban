#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Position.h"

class GameObject {
protected:
	int gameMode;
	Position position;
	Texture texture;
	Sprite sprite;
};

#endif // GAME_OBJECT_H