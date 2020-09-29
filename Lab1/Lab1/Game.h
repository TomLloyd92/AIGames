#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Gameplay.h"
#include "Globals.h"


class Game
{
public:
	Game();
	~Game();
	void run();

private:
	//Game Loop
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void setupAssets();
	static GameMode m_currentMode;

	//Font
	sf::Font m_ArialBlackfont;

	//Screens
	sf::RenderWindow m_window;
	GamePlay m_gameplayScreen;
	bool m_exitGame;
};

#endif
