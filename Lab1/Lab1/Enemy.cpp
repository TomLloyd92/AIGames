#include "Enemy.h"

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{
}

void Enemy::update(sf::Time t_deltaTime)
{
	m_movement();
	m_textEnemy.setPosition(m_pos.x + 100, m_pos.y);
}

void Enemy::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_enemyShape);
	t_window.draw(m_textEnemy);
}

void Enemy::setup(sf::Font &t_font)
{
	m_shipColour = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	m_textEnemy.setFillColor(sf::Color(0, 255, 255));
	m_textEnemy.setCharacterSize(75);
	m_textEnemy.setFont(t_font);

	initialise();
}

void Enemy::initialise()
{
	m_pos.x = rand() % SCREEN_WIDTH + 1.0f;
	m_pos.y = rand() % SCREEN_HEIGHT + 1.0f;
	m_enemyShape.setPointCount(3);
	m_enemyShape.setFillColor(m_shipColour);
	m_enemyShape.setRadius(m_ENEMY_RADIUS * 2);
	m_enemyShape.setPosition(m_pos);
	m_enemyShape.setOrigin(m_ENEMY_RADIUS * 2, m_ENEMY_RADIUS * 2);
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
		return	std::atan2f(-t_velocity.x, t_velocity.y) / DEG_TO_RAD; ;
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
