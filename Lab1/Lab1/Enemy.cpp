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

void Enemy::wander()
{	
	futureLocation.x = m_vel.x * m_PREDICTED_LENGTH;
	futureLocation.y = m_vel.y * m_PREDICTED_LENGTH;
	futureLocation = futureLocation + m_pos;

	m_vel = futureLocation - m_pos;

	m_rotation = getNewOrientation(m_rotation, m_vel);

	m_rotation = m_rotation + (m_MAX_ROTATION * ((rand() % 2) - 0.5));



	setVelocity(sf::Vector2f(-std::sin(m_rotation * DEG_TO_RAD), std::cos(m_rotation * DEG_TO_RAD)) * m_MAX_FORCE);
}

void Enemy::seekOrFlee(std::string seekOrFlee, sf::Vector2f t_target)
{
	sf::Vector2f relevantLocation;
	if (seekOrFlee == "seek") 
	{
		//SEEK
		relevantLocation = t_target - m_pos;
	}
	else if (seekOrFlee == "flee")
	{
		//FLEE
		relevantLocation = m_pos - t_target;
	}

	//Unit vector
	relevantLocation = m_vectorMaths.unitVec(relevantLocation);

	//Scale to Speed
	relevantLocation = relevantLocation * m_speed;

	//Subtract velocity from desiered
	sf::Vector2f steering = relevantLocation + m_vel;

	//Limit Max force
	float magnitudeSteering = m_vectorMaths.magnitude(steering);
	if (magnitudeSteering > m_MAX_FORCE)
	{
		sf::Vector2f unitSteering = steering / magnitudeSteering;
		steering = unitSteering * m_MAX_FORCE;
	}

	//Convert Velocity Vector into Rotation
	//float dest = std::atan2f(-1.0f * steering.y, -1.0f * steering.x) / PI * 180 + 180;

	//Convert Velocity Vector into Rotation
	//float dest = std::atan2f(-steering.x, steering.y) / DEG_TO_RAD;

	//Apply Rotation
	setRotiation(getNewOrientation(m_rotation, steering));

	//Apply Steering
	setVelocity(steering);
}

void Enemy::arrive(sf::Vector2f t_target)
{
	sf::Vector2f relevantLocation;

	relevantLocation = t_target - m_pos;

	if (m_vectorMaths.magnitude(relevantLocation) > 300)
	{
		m_enemyShape.setFillColor(sf::Color(255, 0, 0));
		m_MAX_FORCE = 10;
	}
	else if (m_vectorMaths.magnitude(relevantLocation) < 300)
	{
		m_enemyShape.setFillColor(sf::Color(255, 255, 255));
		m_MAX_FORCE = 10 * (m_vectorMaths.magnitude(relevantLocation) / 300);
	}

	//Unit vector
	relevantLocation = m_vectorMaths.unitVec(relevantLocation);

	//Scale to Speed
	relevantLocation = relevantLocation * m_speed;

	//Subtract velocity from desiered
	sf::Vector2f steering = relevantLocation + m_vel;

	//Limit Max force
	float magnitudeSteering = m_vectorMaths.magnitude(steering);

	if (magnitudeSteering > m_MAX_FORCE)
	{
		sf::Vector2f unitSteering = steering / magnitudeSteering;
		steering = unitSteering * m_MAX_FORCE;
	}

	//Convert Velocity Vector into Rotation
	float dest = std::atan2f(-steering.x, steering.y) / DEG_TO_RAD;

	//Apply Rotation
	setRotiation(getNewOrientation(m_rotation, steering));

	//Apply Steering
	setVelocity(steering);

}

float Enemy::getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity)
{
	if (m_vectorMaths.magnitude(t_velocity) > 0)
	{
		return	std::atan2f(-t_velocity.x, t_velocity.y) / DEG_TO_RAD; ;
	}
	else
	{
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
