#include "Backgroud.h"

Background::Background() {}

void Background::display(RenderWindow& renderWindow) {
	renderWindow.draw(sprite);
}

void Background::setTexture(Texture& texture) {
	this->texture = Texture(texture);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(Vector2f(0, 0));
}