#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <queue>
#include "Node.h"
#include "Globals.h"

class Grid
{
public:
	Grid();
	~Grid();
	void update();
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font& t_font);
	void initialise();
	void visit(Node* t_node);

	//Updates
	void updateArc();
	void updateArrow();
	void updatePath();

	//Sets
	void setImpassibleNode(sf::Vector2i t_impassibleNode);
	void setGoal(sf::Vector2i t_goalNode);
	void setStart(sf::Vector2i t_startNode);

	//Algorithms
	void aStar();
	void createFlowField();

	void resetPaths();
	void setVectors();

private:
	int startNode = 13;
	int goalNode = 15;
};
