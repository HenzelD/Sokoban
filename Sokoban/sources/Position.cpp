#include "Position.h"

Position::Position() {
	this->x = 0;
	this->y = 0;
}

Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

Vector2f Position::toVector2f(int gameMode) {
	return Vector2f(this->x * (120 / gameMode), this->y * (120 / gameMode));
}

bool Position::operator==(Position compareTo) {
	return this->x == compareTo.x && this->y == compareTo.y;
}

int Position::getX() {
	return this->x;
}
int Position::getY() {
	return this->y;
}
void Position::setX(int x) {
	this->x = x;
}
void Position::setY(int y) {
	this->y = y;
}
void Position::goLeft() {
	this->x--;
}
void Position::goRight() {
	this->x++;
}
void Position::goUp() {
	this->y--;
}
void Position::goDown() {
	this->y++;
}