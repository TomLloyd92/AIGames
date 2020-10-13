#include "Gameplay.h"

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time t_deltaTime)
{
	//Update Player
	m_player.update(t_deltaTime);

	//Update Enemys
	m_arriveEnemy.update(t_deltaTime);
	m_fleeEnemy.update(t_deltaTime);
	m_wanderEnemy.update(t_deltaTime);

	//Enemy AI Behaviours	
	m_arriveEnemy.arrive(m_player.getPos());
	m_fleeEnemy.seekOrFlee("flee", m_player.getPos());
	m_wanderEnemy.wander();
}

void GamePlay::render(sf::RenderWindow& t_window)
{
	//Draw Player
	m_player.render(t_window);

	//Draw Enemys
	m_arriveEnemy.render(t_window);
	m_fleeEnemy.render(t_window);
	m_wanderEnemy.render(t_window);
}

void GamePlay::setup()
{
	//Setup Player
	m_player.setup();

	//setup Enemys
	m_arriveEnemy.setup();
	m_fleeEnemy.setup();
	m_wanderEnemy.setup();
}

void GamePlay::initialise()
{
}
