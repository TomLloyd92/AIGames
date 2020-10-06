#pragma once
#pragma once
#include <iostream>
#include "Globals.h"
#include "cmath"
#include <SFML/Graphics.hpp>
#include "Globals.h"

class VectorMaths
{

public:
	VectorMaths();
	float magnitude(sf::Vector2f t_vec1);
	sf::Vector2f unitVec(sf::Vector2f t_vec1);
	float angleBetween(sf::Vector2f t_vec1, sf::Vector2f t_vec2);
	float dotProduct(sf::Vector2f t_vec1, sf::Vector2f t_vec2);
	sf::Vector2f scalerProduct(sf::Vector2f t_vec1, sf::Vector2f t_vec2, float t_angle);
};