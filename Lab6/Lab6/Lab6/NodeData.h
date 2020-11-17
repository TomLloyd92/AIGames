#pragma once
#include  <string>
#include "SFML\Graphics.hpp"
// ---------------------------------------------------------------------
//  Name:           NodeData
//  Description:    A simple struct to encapsulate all the node data.
//                  Add or remove fields as required.               
// ---------------------------------------------------------------------
struct NodeData
{
	std::string m_name;
	int xPos;
	int yPos;

	int m_h{ 0 };
	int m_g{ 0 };

	bool passable;

	sf::RectangleShape rectangle;


};
