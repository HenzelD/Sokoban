#include "Target.h"

Target::Target(int gameMode) {
	this->gameMode = gameMode;
}

void Target::display(RenderWindow& renderWindow) {
	renderWindow.draw(sprite);
}

Position Target::getPosition() {
	return this->position;
}

void Target::setPosition(Position position) {
	this->position = position;
}

void Target::setTexture(Texture& texture) {
	this->texture = Texture(texture);
	this->sprite = Sprite(this->texture);
	this->sprite.setPosition(this->position.toVector2f(gameMode));
}