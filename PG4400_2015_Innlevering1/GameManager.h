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
	bool Play(const double dt);
	void MainMenu();
	void Options();
	void Highscores();

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	Level level;
	Player player;
	Ball ball;
	Timer logicTimer;
	Timer drawTimer;

	unsigned short gameState;
	std::shared_ptr<EventHandler> eventHandler;
	std::shared_ptr<InputManager> inputManager;


	bool run;
};

#endif