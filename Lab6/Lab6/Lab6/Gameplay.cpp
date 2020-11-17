#include "Gameplay.h"

GamePlay::GamePlay()
{

}

GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time t_deltaTime)
{
	//Input
	//input();

	testLevel.update(t_deltaTime);
}

void GamePlay::render(sf::RenderWindow& t_window)
{
	testLevel.render(t_window);
}

void GamePlay::setup(sf::Font& t_font)
{


}

void GamePlay::initialise()
{
}

void GamePlay::input()
{
	
}
