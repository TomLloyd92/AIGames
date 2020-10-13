#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "AIController.h"
#include <array>

class GamePlay
{
public:
	GamePlay();
	~GamePlay();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font& t_font);
	void initialise();
private:
	//Font
	sf::Font m_font;

	//Objects
	Player m_player;
	Enemy m_arriveEnemy;
	Enemy m_seekEnemy;
	Enemy m_wanderEnemy;

	//AI Controller
	AIController m_AIController;
	
};