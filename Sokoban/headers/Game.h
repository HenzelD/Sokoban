#ifndef GAME_H
#define GAME_H

#include <string>

#include "Player.h"
#include "Target.h"
#include "Backgroud.h"

class Game {
private:
	bool resourcesLoaded;

	bool gameActive;
	bool victory;

	int gameMode;
	int boxesNumber;
	int maxX;
	int maxY;

	Texture wallTexture;
	Texture targetTexture;
	Texture boxTexture;

	Texture victoryTexture;
	Sprite victorySprite;

	Player player;
	Background background;
	std::vector<Wall*> walls;
	std::vector<Box*> boxes;
	std::vector<Target*> targets;

	Position randomPosition();

	bool isPositionOfWall(Position position);
	bool isPositionOfTarget(Position position);
	bool isPositionOfBox(Position position);
	bool isNextToWall(Position position);

	void generateWalls();
	void generateTargets();
	void generateBoxes();

	void displayWalls(RenderWindow& renderWindow);
	void displayTargets(RenderWindow& renderWindow);
	void displayBoxes(RenderWindow& renderWindow);

	int handleKeyEvent(RenderWindow& renderWindow, Event& event);
	bool areAllBoxesOnTargets();
	void handleDirection(int direction);
	void handleVictory(RenderWindow& renderWindow);
	void displayGame(RenderWindow& renderWindow);

	bool loadResources();
	void clearBoard();
	void prepareBoard();
	void handleGameLoop(RenderWindow& renderWindow, Event& event);

public:
	Game(int gameMode);
	void play();
};

#endif // GAME_H