#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include "Globals.h"

class Node
{
public:
	Node();
	~Node();
	void update();


	//Gets
	float getWeight() { return m_weight; };
	sf::Vector2f getPos() { return m_pos; };
	bool getPassable() { return m_passable; };
	sf::RectangleShape rectangle;
	sf::Text getTextWeight() { return m_text; };
	bool getMarked() { return m_marked; };
	bool getPath() { return m_path; };

	//Sets
	void setWeight(float t_weight) { m_weight = t_weight; };
	void setPos(sf::Vector2f t_newPos) {m_pos = t_newPos; };
	void setPassable(bool t_passable) { m_passable = t_passable; };
	void setUp(sf::Font t_font);
	void setMarked(bool t_true) { m_marked = t_true; };
	void setPathNode(bool t_path) { m_path = t_path; };

	//Arcs
	void setArc(Node* t_node);
	void removeArc(Node* t_node);
	std::list<Node*> getArcs() { return m_arcs; };

	//Vector
	void setVector(sf::Vector2f t_vector) { vectorToNextNode = t_vector; };

private:
	sf::Vector2f m_pos;
	int m_weight = 1;
	bool m_passable = true;
	bool m_marked = false;
	bool m_path = false;

	std::list<Node*> m_arcs;

	sf::Vector2f vectorToNextNode;

	//Text
	sf::Font m_font;
	sf::Text m_text;
};