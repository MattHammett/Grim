#include "../Include/Engine.h"
#include "../Include/Setup.h"
#include "../Include/Utility/Singletons.h"
#include "../Include/Utility/Math/Constants.h"
#include "../Include/Debug/Error.h"

#include <SFML\Window\Event.hpp>
#include <iostream>
using namespace Grim;

Engine::Engine()
{
	Error::changeSFMLrdbuff();
	if (!tryInitializeSingletons()) return;
	if (!tryInitializeWindow()) return;
	if (!tryRunGameLoop()) return;
}

Engine::~Engine()
{
}

void Engine::run()
{
	m_t = 0.0f;
	m_dt = GRIM_DELTA_TIME;
	
	m_CurrentTime = Singletons::clock.getElapsedTimeSeconds();
	m_Accumulator = 0.0f;

	while (m_Running)
	{
		m_NewTime = Singletons::clock.getElapsedTimeSeconds();
		m_FrameTime = m_NewTime - m_CurrentTime;
		if (m_FrameTime > 0.25f)
		{
			m_FrameTime = 0.25f;
		}
		m_CurrentTime = m_NewTime;
		m_Accumulator += m_FrameTime;

		sf::Event events;
		while (m_RenderWindow.pollEvent(events))
		{
			if (events.type == events.Closed)
			{
				exit();
			}
			if (events.type == events.KeyPressed && events.key.code == sf::Keyboard::Space)
			{
				Singletons::lua.testFunction();
			}
		}

		while (m_Accumulator >= m_dt)
		{
			m_StatePrevious = m_StateCurrent;
			integrate(m_StateCurrent, m_dt);
			m_t += m_dt;
			m_Accumulator -= m_dt;
		}

		//std::cout << Singletons::clock.getElapsedTimeSeconds() << std::endl;

		m_FrameAlpha = m_Accumulator / m_dt;
		float32 stateRender = m_StateCurrent * m_FrameAlpha + m_StatePrevious * (1.0f - m_FrameAlpha);

		render(stateRender);
	}
	m_ExitCode = GRIM_EXIT_SUCCESS;
}

void Engine::exit()
{
	m_Running = false;
	m_RenderWindow.close(); 
}

void Engine::setExitCode(int32 exitCode)
{
	m_ExitCode = exitCode;
}

int32 Engine::getExitCode() const
{
	return m_ExitCode;
}

bool Engine::tryInitializeSingletons()
{
	try
	{
		Singletons::initialize();
	}
	catch (Error::Type error)
	{
		Singletons::log.print(Singletons::strings.find("ENGINE_SINGLETONS_INITIALIZATION_ERROR"));
		Error::handle(error, *this);
		return false;
	}
	catch (rapidxml::parse_error)
	{
		Error::handleXMLParse();
		return false;
	}
	return true;
}

bool Engine::tryInitializeWindow()
{
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 8;
	contextSettings.antialiasingLevel = 4;
	contextSettings.majorVersion = 4;
	contextSettings.minorVersion = 5;

	m_RenderWindow.create(sf::VideoMode(1280, 720, 32), Singletons::strings.find("ENGINE_WINDOW_TITLE"), sf::Style::Close, contextSettings);
	Singletons::log.print(Log::Level::sf, Error::convertSFML());
	//m_RenderWindow.setVerticalSyncEnabled(1);

	return true;
}

bool Engine::tryRunGameLoop()
{
	try
	{
		m_Running = true;
		Engine::run();
	}
	catch (Error::Type error)
	{
		Singletons::log.print(Singletons::strings.find("ENGINE_RUNTIME_ERROR"));
		Error::handle(error, *this);
		return false;
	}
	Singletons::log.print(Singletons::strings.find("ENGINE_SHUTTING_DOWN"));
	Singletons::terminate();
	return true;
}

void Engine::integrate(float32 stateCurrent, float32 dt)
{
	m_Player.update(m_RenderWindow, dt);
}

void Engine::render(float32 stateRender)
{
	m_RenderWindow.clear(sf::Color::Black);
	m_RenderWindow.draw(m_Player);
	m_RenderWindow.display();
}
