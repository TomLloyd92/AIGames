#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "GraphArc.h"
#include "GraphNode.h"
#include "NodeData.h"
#include "Globals.h"

typedef GraphArc<NodeData, int> Arc;
typedef GraphNode<NodeData, int> Node;

class TestLevel
{
public:
	TestLevel();
	~TestLevel();
	void update();
	void render(sf::RenderWindow& t_window);
	void setup(sf::Font& t_font);
	void initialise();
	void visit(Node* t_node);

	//Updates
	void updateArc();

	//Sets
	void setImpassibleNode(sf::Vector2i t_impassibleNode);
	void setGoal(sf::Vector2i t_goalNode);
	void setStart(sf::Vector2i t_startNode);

	//Algorithms
	void aStar();
	void breathFirst();
	void createFlowField();

private:
	int startNode = 0;
	int goalNode = 2499;
};
