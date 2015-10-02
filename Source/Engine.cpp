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
	tryInitializeSingletons();
	tryInitializeWindow();
	tryRunGameLoop();
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
				Engine::exit();
			}
		}

		while (m_Accumulator >= m_dt)
		{
			m_StatePrevious = m_StateCurrent;
			//intergrate(currentState, t, dt);
			m_t += m_dt;
			m_Accumulator -= m_dt;
		}

		m_FrameAlpha = m_Accumulator / m_dt;
		float32 renderState = m_StateCurrent * m_FrameAlpha + m_StatePrevious * (1.0f - m_FrameAlpha);

		//Render(renderState);
		m_RenderWindow.clear(sf::Color::Black);
		m_RenderWindow.display();
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
	contextSettings.depthBits = 32;
	contextSettings.stencilBits = 8;
	contextSettings.antialiasingLevel = 4;
	contextSettings.majorVersion = 3;
	contextSettings.minorVersion = 0;
	uint32 style = sf::Style::Close;

	Error::changeSFMLrdbuff();
	m_RenderWindow.create(sf::VideoMode(1280, 720, 32), Singletons::strings.find("ENGINE_WINDOW_TITLE"), style, contextSettings);
	Singletons::log.print(Log::Level::sf, Error::convertSFML());

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
