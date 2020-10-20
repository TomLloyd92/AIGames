#include "Enemy.h"

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{
}

void Enemy::update(sf::Time t_deltaTime, Player & t_player)
{
	//Update Move
	m_movement();

	//Update View
	m_viewUpdate(t_player);
	
	m_textEnemy.setPosition(m_pos.x + 100, m_pos.y);
}

void Enemy::render(sf::RenderWindow& t_window)
{
	//Draw Enemy
	t_window.draw(m_enemyShape);
	//Draw Vision
	t_window.draw(m_view);
	//Draw text
	t_window.draw(m_textEnemy);
}

void Enemy::setup(sf::Font &t_font)
{
	m_shipColour = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	m_textEnemy.setFillColor(m_shipColour);
	m_textEnemy.setCharacterSize(50);
	m_textEnemy.setFont(t_font);

	initialise();
}

void Enemy::initialise()
{
	//Random Starting Pos
	m_pos.x = rand() % SCREEN_WIDTH + 1.0f;
	m_pos.y = rand() % SCREEN_HEIGHT + 1.0f;

	//Setting up Enemy
	m_enemyShape.setPointCount(3);
	m_enemyShape.setFillColor(m_shipColour);
	m_enemyShape.setRadius(m_ENEMY_RADIUS * 2);
	m_enemyShape.setPosition(m_pos);
	m_enemyShape.setOrigin(m_ENEMY_RADIUS * 2, m_ENEMY_RADIUS * 2);

	//Setting up Vision

	//Random starting Vel
	setVelocity(sf::Vector2f((rand() % 6) -3, (rand() % 6) -3));
}

void Enemy::increaseSpeed()
{
	if (m_speed < m_MAX_SPEED)
	{
		m_speed += 0.1;
	}
}



float Enemy::getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity)
{
	//New Orientation if moving
	if (m_vectorMaths.magnitude(t_velocity) > 0)
	{
		return	std::atan2f(-t_velocity.x, t_velocity.y) * RAD_TO_DEG;
	}
	else
	{
		//Same orientation if standing still
		return t_currentOrientation;
	}
}

void Enemy::m_movement()
{
	m_pos = m_pos + m_vel;

	if (m_pos.x > SCREEN_WIDTH)
	{
		m_pos.x = 0;
	}
	else if (m_pos.x < 0)
	{
		m_pos.x = SCREEN_WIDTH;
	}

	if (m_pos.y > SCREEN_HEIGHT)
	{
		m_pos.y = 0;
	}
	else if (m_pos.y < 0)
	{
		m_pos.y = SCREEN_HEIGHT;
	}

	
	m_enemyShape.setPosition(m_pos);
	m_enemyShape.setRotation(m_rotation + m_ROTATION_OFFSET);

	increaseSpeed();
}

void Enemy::m_viewUpdate(Player t_player)
{
	//clear line
	m_view.clear();

	//Get the distance length to see if is in range
	sf::Vector2f distanceVec =  t_player.getPos() - m_pos;
	float distance = m_vectorMaths.magnitude(distanceVec);

	//Not Seen
	if (distance > m_SIGHT_RANGE)
	{
		m_viewColour = sf::Color::Green;
	}
	//Seen
	else if(distance <= m_SIGHT_RANGE)
	{
		//Get dir of target
		sf::Vector2f dirToTarget = t_player.getPos() - m_pos;

		//Find the angle between
		float angleBetween = m_vectorMaths.angleBetween(dirToTarget, m_vel );

		//Seen inside the cone
		if (angleBetween < m_SIGHT_ANGLE)
		{
			m_viewColour = sf::Color::Red;
		}
		//Not seen outside
		else if (angleBetween > m_SIGHT_ANGLE)
		{
			m_viewColour = sf::Color::Green;
		}
	}

	//Append
	//Draw the line
	sf::Vector2f currentVelUnit = m_vectorMaths.unitVec(m_vel);
	m_viewStart = sf::Vertex(sf::Vector2f{ m_pos.x, m_pos.y}, m_viewColour);
	m_viewEnd = sf::Vertex(sf::Vector2f{ (m_pos.x +  (currentVelUnit.x) * m_SIGHT_RANGE), m_pos.y + currentVelUnit.y * m_SIGHT_RANGE}, m_viewColour);

	m_view.append(m_viewStart);
	m_view.append(m_viewEnd);
}
