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
	GAMEOVER,
	EXIT
};

class GameManager
{
	friend class Ball;
	friend class Player;

public:
	int WindowWidth;
	int WindowHeight;

	GameManager(SDL_Window* window, SDL_Renderer* renderer);
	~GameManager();
	void Run();

	void SetupGame(const std::string& nextLevel);
	bool Play(const double dt, std::string levelName);
	void MainMenu();
	void GameOver();


	static const SDL_Rect& GetWindowRectangle();

private:
	int selection;
	static SDL_Window *window;
	static SDL_Renderer *renderer;

	Level level;
	Timer logicTimer;
	Timer drawTimer;

	unsigned short gameState;
	std::shared_ptr<EventHandler> eventHandler;
	std::shared_ptr<InputManager> inputManager;
	bool run;

	GameObject menu;
	GameObject gameOver;

protected:
	static Player player;
	static std::vector<Ball> balls;
	std::vector<PowerUp> powMap;
};

#endif