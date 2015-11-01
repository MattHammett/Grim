#include "Engine.h"
#include "Setup.h"
#include "Utility/Singletons.h"
#include "Utility/Math/Constants.h"
#include "Debug/Error.h"
#include <SFML\Graphics.hpp>

#include <SFML\Window\Event.hpp>
#include <iostream>
using namespace Grim;

Engine::Engine()
{
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

	auto desk = std::make_shared<Desktop>();
	auto cont = std::make_shared<Container>();
	auto lab = std::make_shared<Label>();
	cont->add(lab);
	desk->add(cont);

	Singletons::gui.add(desk);

	while (m_bRunning)
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
			Singletons::gui.handle(m_RenderWindow, events);
		}
		Singletons::input.checkStates();

		while (m_Accumulator >= m_dt)
		{
			m_StatePrevious = m_StateCurrent;

			// Tick here

			m_t += m_dt;
			m_Accumulator -= m_dt;
		}

		m_FrameAlpha = m_Accumulator / m_dt;
		float32 stateRender = m_StateCurrent * m_FrameAlpha + m_StatePrevious * (1.0f - m_FrameAlpha);

		render(stateRender);
	}
	m_ExitCode = GRIM_EXIT_SUCCESS;
}

void Engine::exit()
{
	m_bRunning = false;
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
	Error::changeSFMLrdbuff();
	try
	{
		Singletons::initialize();
	}
	catch (Error::Type error)
	{
		Singletons::log.print(Singletons::resources.findString("ENGINE_SINGLETONS_INITIALIZATION_ERROR"));
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

	m_RenderWindow.create(sf::VideoMode(1280, 720, 32), Singletons::resources.findString("ENGINE_WINDOW_TITLE"), sf::Style::Close, contextSettings);
	Singletons::log.print(Log::Level::sf, Error::convertSFML());
	//m_RenderWindow.setVerticalSyncEnabled(1);
	Singletons::log.print(Log::Level::Verbose, Singletons::resources.findString("ENGINE_SFML_WINDOW_INITIALIZED"));

	Singletons::log.print(Log::Level::Info, Singletons::resources.findString("ENGINE_INITIALIZED"));
	return true;
}

bool Engine::tryRunGameLoop()
{
	try
	{
		m_bRunning = true;
		Engine::run();
	}
	catch (Error::Type error)
	{
		Singletons::log.print(Singletons::resources.findString("ENGINE_RUNTIME_ERROR"));
		Error::handle(error, *this);
		return false;
	}
	Singletons::log.print(Singletons::resources.findString("ENGINE_SHUTTING_DOWN"));
	Singletons::terminate();
	return true;
}

void Engine::render(float32 stateRender)
{
	m_RenderWindow.clear(sf::Color::Black);
	Singletons::gui.render(m_RenderWindow, sf::RenderStates());
	m_RenderWindow.display();
}
