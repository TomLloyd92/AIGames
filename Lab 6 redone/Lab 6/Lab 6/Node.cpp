#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

void Node::update()
{
    //Set Rec Pos
	rectangle.setPosition(m_pos);
    //Update string weight
    m_text.setString(std::to_string(m_weight));
    //Set text to sit on relevent cube
    m_text.setPosition(rectangle.getPosition() + (sf::Vector2f(TILE_WIDTH /2, TILE_WIDTH/2)));
    //Clear all marked nodes on update
    m_marked = false;
}

void Node::setUp(sf::Font t_font)
{
    //Set up font and text
    m_font = t_font;
    m_text.setFont(m_font);
    m_text.setFillColor(sf::Color::Black);
    m_text.setCharacterSize(10);
    m_text.setString(std::to_string(m_weight));
}



void Node::setArc(Node* t_node)
{
    //Add Node pointer to arcs list
	m_arcs.push_back(t_node);
}

void Node::removeArc(Node* t_node)
{
    //Create iterator for begining and end
    auto iter = m_arcs.begin();
    auto endIter = m_arcs.end();

    //get amount of arcs
    int size = m_arcs.size();
    // find the arc that matches the node
    for (; iter != endIter && m_arcs.size() == size; ++iter)
    {
        //if node is found
        if (*iter == t_node)
        {
            //erase the node from the list
            m_arcs.erase(iter);
            break;
        }
    }
}
