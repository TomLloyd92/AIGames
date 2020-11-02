#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "AIController.h"
#include <array>
#include "VectorMaths.h"


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
	Enemy m_seekEnemyFast;
	Enemy m_wanderEnemy;
	Enemy m_pursueEnemy;

	//AI Controller
	AIController m_AIController;

	//Bools to display Enemys
	bool m_displayPursue;
	bool m_displayArrive;
	bool m_displaySeek;
	bool m_displaySeekFast;
	bool m_displayWander;

	//Input
	void input();
	float inputTimer = 100;

	//C formation
	void cFormation();

	std::vector<Enemy> Cflock;
	const int CflockSize = 40;

	//Vec Maths
	VectorMaths m_vecMaths;
};