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
	GameManager(SDL_Window* window, SDL_Renderer* renderer);
	~GameManager();
	void Run();

	void SetupGame(const std::string& nextLevel);
	bool Play(const double dt, std::string levelName);
	void MainMenu();
	void GameOver();


	static const SDL_Rect& GetWindowRectangle();

private:
	bool run;
	int selection;
	unsigned short gameState;
	static SDL_Window *window;
	static SDL_Renderer *renderer;

	Level level;
	Timer logicTimer;
	Timer drawTimer;

	// Only used for drawing the menu and game screens
	GameObject menu;
	GameObject gameOver;

	std::shared_ptr<EventHandler> eventHandler;
	std::shared_ptr<InputManager> inputManager;


protected:
	static Player player;
	static std::vector<Ball> balls;
	std::vector<PowerUp> powMap;
};

#endif