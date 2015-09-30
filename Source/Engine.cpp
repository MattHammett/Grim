#include "../Include/Engine.h"
#include "../Include/Setup.h"
#include "../Include/Utility/Singletons.h"
#include <SFML\Window\Event.hpp>
#include <iostream>
using namespace Grim;

Engine::Engine()
{
	Singletons::initialize();

	m_Running = true;
	m_RenderWindow.create(sf::VideoMode(1280, 720, 32), "Grim", sf::Style::Close);
}

Engine::~Engine()
{
	Singletons::terminate();
}

int32 Engine::run()
{
	while (m_Running)
	{
		sf::Event e;

		while (m_RenderWindow.pollEvent(e))
		{
			if (e.type == e.Closed)
			{
				Engine::exit();
			}
		}

		m_RenderWindow.clear(sf::Color::Black);
		m_RenderWindow.display();
	}
	return GRIM_EXIT_SUCCESS;
}

void Engine::exit()
{
	m_Running = false;
	m_RenderWindow.close();
}
