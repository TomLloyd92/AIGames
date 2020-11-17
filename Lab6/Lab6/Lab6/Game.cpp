#include "Game.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Gameplay.h"
#include "Globals.h"

GameMode Game::m_currentMode{ GameMode::Gameplay };

Game::Game() : m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32 }, "Tom Lloyd Lab 6 AI Games" }, m_exitGame{ false }
{
	setupAssets();
}

Game::~Game()
{
	srand(time(NULL));
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.f);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
			render();
		}
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type)
		{
			if ((sf::Keyboard::Escape == event.key.code) && (Game::m_currentMode == GameMode::Gameplay))
			{
				//Pause
			}
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	switch (m_currentMode)
	{
	case GameMode::Gameplay:
		m_gameplayScreen.update(t_deltaTime);
		break;
	default:
		break;
	}

	if (m_exitGame)
	{
		m_window.close();
	}
}

void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	switch (m_currentMode)
	{
	case GameMode::Gameplay:
		m_gameplayScreen.render(m_window);
		break;
	default:
		break;
	}

	m_window.display();
}

void Game::setupAssets()
{
	//Setting up Font
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\Starduster3D-XOvP.otf"))
	{
		//std::cout << "problem loading arial Stardust Font" << std::endl;
	}

	m_gameplayScreen.setup(m_ArialBlackfont);
}

