#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "cmath"

class Player
{
public:
	Player();
	~Player();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setup();
	void initialise();

	//Gets
	sf::Vector2f getPos() { return m_pos; };
	sf::Vector2f getVel() { return m_vel; };
	float getRotation() { return m_rotation; };

private:
	//Test Player;
	sf::CircleShape m_playerShape;
	const float m_PLAYER_RADIUS = 10;

	//Position
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;

	//Movement
	void m_movement();
	void m_increaseRotation();
	void m_decreaseRotation();
	void m_increaseSpeed();
	void m_decreaseSpeed();
	void m_movementHandler();
	float m_speed = 0;
	float m_maxSpeed = 100;
	float m_accelerator = 0.5;
	float m_minSpeed = 0;
	float m_rotation = 0;
	float m_rotationCorrection = 45 / 2;
};