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
	friend class Ball;

public:
	int WindowWidth;
	int WindowHeight;

	GameManager(SDL_Window *window, SDL_Renderer *renderer);
	~GameManager();
	void Init();
	void Run();

	void SetupGame(std::string nextLevel);
	bool Play(const double dt, std::string levelName);
	void MainMenu();
	void Options();
	void Highscores();
	void ChangeLevel();

	static const SDL_Rect& GetWindowRectangle();

private:
	static SDL_Window *window;
	static SDL_Renderer *renderer;

	Level level;
	Timer logicTimer;
	Timer drawTimer;

	unsigned short gameState;
	std::shared_ptr<EventHandler> eventHandler;
	std::shared_ptr<InputManager> inputManager;
	bool run;

protected:
	static Player player;
	static std::vector<Ball> balls;
};

#endif