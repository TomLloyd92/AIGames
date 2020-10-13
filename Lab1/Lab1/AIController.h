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
	void arrive(Enemy& t_seeker, sf::Vector2f t_target);
	void pursue(Enemy& t_seeker, sf::Vector2f t_target);
	void wander(Enemy& t_seeker);

private:

	const float m_PREDICTED_LENGTH = 200;
	VectorMaths m_vectorMaths;



};