#include "Desktop.h"
#include "../../Utility/Singletons.h"
#include "../../Debug/Error.h"
using namespace Grim;

Desktop::Desktop()
{
}

void Desktop::handle(sf::RenderWindow& target, sf::Event& events)
{
	for (auto& it : m_Components)
	{
		it->handle(target, events);
	}
}

void Desktop::tick(sf::RenderWindow& target, float32 dt)
{
	for (auto& it : m_Components)
	{
		it->tick(target, dt);
	}
}

void Desktop::render(sf::RenderTarget& target, sf::RenderStates& state)
{
	for (auto& it : m_Components)
	{
		it->render(target, state);
	}
}

void Desktop::add(Component::Pointer component)
{
	assert(component != nullptr);
	if (component != nullptr)
	{
		m_Components.emplace_back(component);
	}
	else
	{
		Singletons::log.print(Singletons::resources.findString("GUI_DESKTOP_NULLPTR"));
		throw Error::Fatal;
	}
}
