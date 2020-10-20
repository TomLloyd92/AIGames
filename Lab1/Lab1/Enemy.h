#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include <time.h>
#include "VectorMaths.h"
#include <iostream>
#include <cmath>

class Enemy
{
public:
	Enemy();
	Enemy(float t_maxSpeed) { m_MAX_SPEED = t_maxSpeed; };
	~Enemy();
	void update(sf::Time t_deltaTime, Player &t_player);
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font &t_font);
	void initialise();

	//Gets
	sf::Vector2f getPos() { return m_pos; };
	sf::Vector2f getVel() { return m_vel; };
	float getMaxForce() { return m_maxForce; };
	float getMaxSpeed() { return m_MAX_SPEED; };
	float getSpeed() { return m_speed; };
	float getRotation() { return m_rotation; };
	float getMaxRotation() { return m_maxRotation; };
	float getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity);

	//Sets
	void setVelocity(sf::Vector2f t_vel) { m_vel = t_vel; };
	void setRotiation(float t_rotation) { m_rotation = t_rotation; };
	void setMaxForce(float t_maxForce) { m_maxForce = t_maxForce; };
	void setOrientation(float t_orientation) { m_rotation = t_orientation; };
	void increaseSpeed();
	void setText(std::string t_text) { m_textEnemy.setString(t_text); };

	//View
	//View Update
	void m_viewUpdate(Player t_player);

private:
	//Test Circle
	sf::CircleShape m_enemyShape;
	sf::CircleShape m_vision;
	sf::RectangleShape line;
	sf::Vector2f m_pos;
	sf::Vector2f m_vel = { 0,0 };
	sf::Vector2f m_target;
	const float m_ENEMY_RADIUS = 5;
	float m_rotation = 0;

	//Movement
	void m_movement();
	sf::Vector2f m_steering;
	float m_MAX_SPEED = .5;
	float m_speed = 0.01;
	float m_maxForce = 10;
	const static int m_ROTATION_OFFSET = 65 ;

	VectorMaths m_vectorMaths;

	const float m_PREDICTED_LENGTH = 1000;

	const float m_maxRotation = 1;

	//Check future location
	sf::Vector2f futureLocation;
	float num = 0;

	//Text
	sf::Text m_textEnemy;

	//color
	sf::Color m_shipColour;

	//View left
	sf::VertexArray m_view{ sf::Lines };
	//View Start
	sf::Vertex m_viewStart;
	//Power left point
	sf::Vertex  m_viewEnd;

	//View
	sf::VertexArray m_viewRight{ sf::Lines };
	sf::Vertex m_viewStartRight;
	//right poiny
	sf::Vertex m_viewEndRight;

	//Total Power
	sf::Vector2f totalPower;


	sf::Color m_viewColour = sf::Color::Green;
	const float m_SIGHT_RANGE = 200;
	float m_SIGHT_ANGLE = 45;

};