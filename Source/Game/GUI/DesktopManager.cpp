#include "DesktopManager.h"
#include "../../Utility/Singletons.h"
#include "../../Debug/Error.h"
#include <assert.h>
using namespace Grim;

void DesktopManager::initialize()
{
	Singletons::log.print(Log::Level::Verbose, Singletons::resources.findString("GUI_INITIALIZED"));
}

void DesktopManager::terminate()
{
	Singletons::log.print(Log::Level::Verbose, Singletons::resources.findString("GUI_TERMINATED"));
}

void DesktopManager::handle(sf::RenderWindow& target, sf::Event& events)
{
	for (auto& it : m_Desktops)
	{
		it->handle(target, events);
	}
}

void DesktopManager::tick(sf::RenderWindow& target, float32 dt)
{
	for (auto& it : m_Desktops)
	{
		it->tick(target, dt);
	}
}

void DesktopManager::render(sf::RenderTarget& target, sf::RenderStates& state)
{
	for (auto& it : m_Desktops)
	{
		it->render(target, state);
	}
}

void DesktopManager::add(Desktop::Pointer desktop)
{
	assert(desktop != nullptr);
	if (desktop != nullptr)
	{
		m_Desktops.emplace_back(desktop);
	}
	else
	{
		Singletons::log.print(Singletons::resources.findString("GUI_DESKTOP_MANAGER_NULLPTR"));
		throw Error::Fatal;
	}
}
