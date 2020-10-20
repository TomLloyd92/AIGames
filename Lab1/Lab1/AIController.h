#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Globals.h"
#include "Enemy.h"
#include "Player.h"
#include "cmath"
#include "VectorMaths.h"

class AIController
{
public:
	AIController();
	~AIController();

	void seekOrFlee(Enemy& t_seeker, sf::Vector2f t_target, std::string t_seekOrFlee);
	void arrive(Enemy& t_seeker, sf::Vector2f t_target, std::string t_arrive);
	void pursue(Enemy& t_seeker, Player t_target);
	void wander(Enemy& t_seeker);

private:

	const float m_PREDICTED_LENGTH = 200;
	const float m_WANDER_RADIUS = 3;
	float m_wanderOrientation = 0;
	VectorMaths m_vectorMaths;

	const float m_MAX_TIME_PREDICTION = 20;
};