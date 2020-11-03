#include "Gameplay.h"

GamePlay::GamePlay()
{
	m_seekEnemyFast.setMaxForce(15);
	srand(time(NULL));

	for (int i = 0; i < CflockSize; i++)
	{
		Enemy enemy;

		Cflock.push_back(enemy);
	}
}

GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time t_deltaTime)
{
	//Update Player
	m_player.update(t_deltaTime);

	//Update Enemys
	/*
	m_arriveEnemy.update(t_deltaTime, m_player);
	m_seekEnemy.update(t_deltaTime,m_player);
	m_wanderEnemy.update(t_deltaTime, m_player);
	m_pursueEnemy.update(t_deltaTime, m_player);
	m_seekEnemyFast.update(t_deltaTime, m_player);
	*/

	//Enemy AI Behaviours
	/*
	m_AIController.pursue(m_pursueEnemy, m_player);
	m_AIController.arrive(m_arriveEnemy, m_player.getPos(), "Arrive");
	m_AIController.seekOrFlee(m_seekEnemy, m_player.getPos(), "Seek");
	m_AIController.wander(m_wanderEnemy);
	m_AIController.seekOrFlee(m_seekEnemyFast, m_player.getPos(), "Seek");
	*/

	for (int i = 0; i < CflockSize; i++)
	{
		Cflock.at(i).update(t_deltaTime, m_player);
	}


	if (formation)
	{
		cFormation();
	}
	else
	{
		for (int i = 0; i < CflockSize; i++)
		{
			m_AIController.wander(Cflock.at(i));
		}
	}
	//Input
	input();
}

void GamePlay::render(sf::RenderWindow& t_window)
{
	//Draw Player
	m_player.render(t_window);

	//Draw Enemys
	/*
	if (m_displayArrive)
	{
		m_arriveEnemy.render(t_window);
	}
	if (m_displaySeek)
	{
		m_seekEnemy.render(t_window);
	}
	if (m_displaySeekFast)
	{
		m_seekEnemyFast.render(t_window);
	}
	if (m_displayWander)
	{
		m_wanderEnemy.render(t_window);
	}
	if (m_displayPursue)
	{
		m_pursueEnemy.render(t_window);
	}
	*/
	for (int i = 0; i < CflockSize; i++)
	{
		Cflock.at(i).render(t_window);
	}
}

void GamePlay::setup(sf::Font& t_font)
{
	//Setup Player
	m_player.setup();

	//setup Enemys
	/*
	m_arriveEnemy.setup(t_font);
	m_seekEnemy.setup(t_font);
	m_wanderEnemy.setup(t_font);
	m_pursueEnemy.setup(t_font);
	m_seekEnemyFast.setup(t_font);
	*/

	for (int i = 0; i < CflockSize; i++)
	{
		Cflock.at(i).setup(t_font);
	}

}

void GamePlay::initialise()
{
}

void GamePlay::input()
{
	if (inputTimer >= 30)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			inputTimer = 0;
			if (formation)
			{
				formation = false;
			}
			else
			{
				formation = true;
			}

		}

		//Arrive
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			inputTimer = 0;
			if (m_displayArrive)
			{
				m_displayArrive = false;
			}
			else
			{
				m_displayArrive = true;
			}

		}
		//Seek
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			inputTimer = 0;
			if (m_displaySeek)
			{
				m_displaySeek = false;
			}
			else
			{
				m_displaySeek = true;
			}
		}
		//Seek Fast
			//Seek
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			inputTimer = 0;
			if (m_displaySeekFast)
			{
				m_displaySeekFast = false;
			}
			else
			{
				m_displaySeekFast = true;
			}
		}

		//Wander
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			inputTimer = 0;
			if (m_displayWander)
			{
				m_displayWander = false;
			}
			else
			{
				m_displayWander = true;
			}

		}
		//Pursue
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			inputTimer = 0;
			if (m_displayPursue)
			{
				m_displayPursue = false;
			}
			else
			{
				m_displayPursue = true;
			}
		}
	}
	else
	{
		inputTimer++;
	}
}

void GamePlay::cFormation()
{
	for (int i = 0; i < CflockSize; i++)
	{
		sf::Vector2f sub(0,0);
		sf::Vector2f sum(0, 0);
		int npcRadius = 10;
		int closeEnough = 10;
		float angleAroundCircle = 0.0;
		sf::Vector2f targetSlot(0, 0);
		sf::Vector2f targetLeader = m_player.getPos();

		
		angleAroundCircle = (float)i / (CflockSize - 1);
		angleAroundCircle = angleAroundCircle * PI * 2;
		float radius = npcRadius / sin(PI / (CflockSize));

		targetSlot = m_player.getPos();
		targetSlot.x = targetSlot.x + radius * cos(angleAroundCircle);
		targetSlot.y = targetSlot.y + radius * sin(angleAroundCircle);
		sub = (targetSlot - m_player.getPos());
		float D = m_vecMaths.magnitude(sub);
		if (D > closeEnough)
		{
			m_AIController.arrive(Cflock.at(i), targetSlot, "Arrive");
		}
		else
		{
			m_AIController.arrive(Cflock.at(i), targetSlot, "Arrive");
		}
	}
}
