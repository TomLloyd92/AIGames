#include "Gameplay.h"

GamePlay::GamePlay()
{

}

GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time t_deltaTime, sf::RenderWindow & t_Window)
{
	//Input
	input(t_Window);
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

void GamePlay::input(sf::RenderWindow & t_window)
{
	//On left click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Get Mouse Position relative to the window
		sf::Vector2i mousePos = sf::Mouse::getPosition(t_window );

		//Make position relative to the Array
		sf::Vector2i relativeArrayPos;
		relativeArrayPos.x = mousePos.x / TILE_WIDTH;
		relativeArrayPos.y = mousePos.y / TILE_WIDTH;
		//Test output
		std::cout << "Mouse X:" << relativeArrayPos.x << " " << "Mouse Y:" << relativeArrayPos.y << std::endl;
		//Make Node Impassible
		testLevel.setImpassibleNode(relativeArrayPos);
		testLevel.update();
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		//Get Mouse Position relative to the window
		sf::Vector2i mousePos = sf::Mouse::getPosition(t_window);

		//Make position relative to the Array
		sf::Vector2i relativeArrayPos;
		relativeArrayPos.x = mousePos.x / TILE_WIDTH;
		relativeArrayPos.y = mousePos.y / TILE_WIDTH;

		testLevel.setGoal(relativeArrayPos);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(t_window);

		//Make position relative to the Array
		sf::Vector2i relativeArrayPos;
		relativeArrayPos.x = mousePos.x / TILE_WIDTH;
		relativeArrayPos.y = mousePos.y / TILE_WIDTH;
		//Test output
		std::cout << "Mouse X:" << relativeArrayPos.x << " " << "Mouse Y:" << relativeArrayPos.y << std::endl;
		//Make Node Impassible
		testLevel.setStart(relativeArrayPos);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		testLevel.update();
		testLevel.aStar();


	}
}

