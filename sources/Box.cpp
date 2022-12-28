#include "Box.h"

Box::Box(int gameMode) {
	this->gameMode = gameMode;
}

void Box::move(int direction) {
	switch (direction) {
	case 1:
		this->position.goRight();
		break;
	case 2:
		this->position.goLeft();
		break;
	case 3:
		this->position.goUp();
		break;
	case 4:
		this->position.goDown();
		break;
	default:
		break;
	}
	this->sprite.setPosition(this->position.toVector2f(gameMode));
}

bool Box::canBeMoved(int direction, std::vector<Wall*> walls, std::vector<Position> boxesPositions) {
	Position forbiddenPosition = this->position;
	switch (direction) {
	case 1:
		forbiddenPosition.goRight();
		break;
	case 2:
		forbiddenPosition.goLeft();
		break;
	case 3:
		forbiddenPosition.goUp();
		break;
	case 4:
		forbiddenPosition.goDown();
		break;
	default:
		break;
	}
	bool canBeMoved = true;
	for (Wall* wall : walls) {
		if (wall->getPosition() == forbiddenPosition) {
			canBeMoved = false;
		}
	}
	for (Position& position : boxesPositions) {
		if (position == forbiddenPosition) {
			canBeMoved = false;
		}
	}
	return canBeMoved;
}

void Box::display(RenderWindow& renderWindow) {
	renderWindow.draw(sprite);
}

Position Box::getPosition() {
	return this->position;
}

void Box::setPosition(Position position) {
	this->position = position;
}

void Box::setTexture(Texture& texture) {
	this->texture = Texture(texture);
	this->sprite = Sprite(this->texture);
	this->sprite.setPosition(this->position.toVector2f(gameMode));
}