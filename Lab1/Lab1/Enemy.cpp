#include "Enemy.h"

Enemy::Enemy()
{
	srand(time(0));
}

Enemy::~Enemy()
{
}

void Enemy::update(sf::Time t_deltaTime)
{
	m_movement();
}

void Enemy::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_enemyShape);
}

void Enemy::setup()
{
	initialise();
}

void Enemy::initialise()
{

	m_pos.x = rand() % SCREEN_WIDTH + 1.0f;
	m_pos.y = rand() % SCREEN_HEIGHT + 1.0f;
	m_enemyShape.setPointCount(3);
	m_enemyShape.setFillColor(sf::Color(255, 0, 0));
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
