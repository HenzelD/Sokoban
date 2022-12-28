#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Background {
private:
	Texture texture;
	Sprite sprite;
public:
	Background();
	void display(RenderWindow& renderWindow);
	void setTexture(Texture& texture);
};

#endif // BACKGROUND_H