#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <memory>
#include <vector>


#include "Timer.h"
#include "Level.h"
#include "Player.h"
#include "Ball.h"
#include "EventHandler.h"

enum Gamestate
{
	MAINMENU,
	PLAY,
	OPTIONS,
	HIGHSCORES,
	EXIT
};

class GameManager
{
public:
	int WindowWidth;
	int WindowHeight;
	GameManager(SDL_Window *window, SDL_Renderer *renderer);
	~GameManager();
	void Init();
	void Run();

	void SetupGame();
	void Play(const double dt);
	void MainMenu();
	void Options();
	void Highscores();

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	Level currentLevel;
	Player player;
	Ball ball;

	unsigned short gameState;
	std::shared_ptr<EventHandler> eventHandler;
	std::shared_ptr<InputManager> inputManager;
	Timer logicTimer;
	Timer drawTimer;

	bool run;
};

#endif