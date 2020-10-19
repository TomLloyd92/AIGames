#include "Gameplay.h"

GamePlay::GamePlay()
{
	srand(time(NULL));
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
	m_seekEnemy.update(t_deltaTime);
	m_wanderEnemy.update(t_deltaTime);
	m_pursueEnemy.update(t_deltaTime);

	//Enemy AI Behaviours	
	m_AIController.pursue(m_pursueEnemy, m_player);
	m_AIController.arrive(m_arriveEnemy, m_player.getPos(), "Arrive");
	m_AIController.seekOrFlee(m_seekEnemy, m_player.getPos(), "Seek");
	m_AIController.wander(m_wanderEnemy);
}

void GamePlay::render(sf::RenderWindow& t_window)
{
	//Draw Player
	m_player.render(t_window);

	//Draw Enemys
	m_arriveEnemy.render(t_window);
	m_seekEnemy.render(t_window);
	m_wanderEnemy.render(t_window);
	m_pursueEnemy.render(t_window);
}

void GamePlay::setup(sf::Font& t_font)
{
	//Setup Player
	m_player.setup();

	//setup Enemys
	m_arriveEnemy.setup(t_font);
	m_seekEnemy.setup(t_font);
	m_wanderEnemy.setup(t_font);
	m_pursueEnemy.setup(t_font);
}

void GamePlay::initialise()
{
}
