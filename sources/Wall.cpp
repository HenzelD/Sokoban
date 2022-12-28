#include "Wall.h"

Wall::Wall(int gameMode) {
	this->gameMode = gameMode;
}

void Wall::display(RenderWindow& renderWindow) {
	renderWindow.draw(sprite);
}

Position Wall::getPosition()
{
	return this->position;
}

void Wall::setPosition(Position position) {
	this->position = position;
}

void Wall::setTexture(Texture& texture) {
	this->texture = Texture(texture);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(this->position.toVector2f(gameMode));
}
