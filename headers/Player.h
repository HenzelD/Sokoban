#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Box.h"

class Player {
private:
	int lastHorizontalMoveDirection; //1-right, 2-left
	int gameMode;
	Position position;
	Texture rightTexture;
	Texture leftTexture;
	Sprite sprite;
public:
	Player();
	~Player();
	void display(RenderWindow &renderWindow);
	bool canMove(int direction, std::vector<Wall*> walls, std::vector<Box*> boxes);
	void move(int direction, std::vector<Box*> boxes); //1-right, 2-left, 3-up, 4-down
	void setPosition(Position position);
	void setTexture(Texture &rightTexture, Texture &leftTexture);
	void setGameMode(int gameMode);
};

#endif // PLAYER_H