#include "VectorMaths.h"

VectorMaths::VectorMaths()
{
}

float VectorMaths::magnitude(sf::Vector2f t_vec)
{
	float x = t_vec.x;
	float y = t_vec.y;

	float magnitude = std::sqrt((x * x) + (y * y));
	return magnitude;
}

sf::Vector2f VectorMaths::unitVec(sf::Vector2f t_vec)
{
	float x = t_vec.x;
	float y = t_vec.y;

	float vectorLength = magnitude(t_vec);
	if (vectorLength != 0)
	{
		x = x / vectorLength;
		y = y / vectorLength;
	}
	return sf::Vector2f(x, y);
}

float VectorMaths::angleBetween(sf::Vector2f t_vec1, sf::Vector2f t_vec2)
{
	float angleInDegrees = dotProduct(unitVec(t_vec1), unitVec(t_vec2));
	angleInDegrees = std::acos(angleInDegrees);
	angleInDegrees = angleInDegrees * RAD_TO_DEG;
	return angleInDegrees;
}

float VectorMaths::dotProduct(sf::Vector2f t_vec1, sf::Vector2f t_vec2)
{
	float dotProduct = (t_vec1.x * t_vec2.x) + (t_vec1.y * t_vec2.y);;

	return dotProduct;
}

sf::Vector2f VectorMaths::scalerProduct(sf::Vector2f t_vec1, sf::Vector2f t_vec2, float t_angle)
{
	float magVec1 = magnitude(t_vec1);
	float scalerProductMag = magVec1 * std::cos(t_angle);

	sf::Vector2f spVec = scalerProductMag * unitVec(t_vec2);

	return spVec;
}
