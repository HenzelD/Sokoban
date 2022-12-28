#include "Player.h"

Player::Player() {
	lastHorizontalMoveDirection = 1;
	gameMode = 1;
}

Player:: ~Player() {

}

void Player::display(RenderWindow &renderWindow) {
	renderWindow.draw(sprite);
}

void Player::move(int direction, std::vector<Box*> boxes) {
	switch (direction) {
	case 1:
		this->position.goRight();
		if (lastHorizontalMoveDirection == 2) {
			lastHorizontalMoveDirection = 1;
			sprite.setTexture(rightTexture);
		}
		break;
	case 2:
		this->position.goLeft();
		if (lastHorizontalMoveDirection == 1) {
			lastHorizontalMoveDirection = 2;
			sprite.setTexture(leftTexture);
		}
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
	for (Box* box : boxes) {
		if (box->getPosition() == this->position) {
			box->move(direction);
		}
	}
}

bool Player::canMove(int direction, std::vector<Wall*> walls, std::vector<Box*> boxes) {
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
	bool canMove = true;
	for (Wall* wall : walls) {
		if (wall->getPosition() == forbiddenPosition) {
			canMove = false;
		}
	}
	std::vector<Position> boxesPositions;
	for (Box* box : boxes) {
		boxesPositions.push_back(box->getPosition());
	}
	for (Box* box : boxes) {
		if (box->getPosition() == forbiddenPosition && !box->canBeMoved(direction, walls, boxesPositions)) {
			canMove = false;
		}
	}
	return canMove;
}

void Player::setPosition(Position position) {
	this->position = position;
	this->sprite.setPosition(position.toVector2f(gameMode));
}

void Player::setTexture(Texture &rightTexture, Texture &leftTexture) {
	this->rightTexture = Texture(rightTexture);
	this->leftTexture = Texture(leftTexture);
	this->sprite.setTexture(this->rightTexture);
}

void Player::setGameMode(int gameMode) {
	this->gameMode = gameMode;
}