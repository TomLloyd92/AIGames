#include "Gameplay.h"

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time t_deltaTime)
{
	m_player.update(t_deltaTime);

	m_enemy.update(t_deltaTime);

	//m_enemy.seekOrFlee("seek", m_player);
	m_enemy.arrive(m_player);
}

void GamePlay::render(sf::RenderWindow& t_window)
{
	m_player.render(t_window);
	m_enemy.render(t_window);
}

void GamePlay::setup()
{
	m_player.setup();
	m_enemy.setup();
}

void GamePlay::initialise()
{
}
