#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include <array>

class GamePlay
{
public:
	GamePlay();
	~GamePlay();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setup();
	void initialise();
private:
	//Font
	sf::Font m_font;

	//Objects
	Player m_player;
	Enemy m_arriveEnemy;
	Enemy m_fleeEnemy;
	Enemy m_wanderEnemy;
};