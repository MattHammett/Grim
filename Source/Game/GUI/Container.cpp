#include "Container.h"
#include "../../Utility/Singletons.h"
#include "../../Debug/Error.h"
#include <assert.h>
using namespace Grim;

Container::Container()
{
}

void Container::handle(sf::RenderWindow& target, sf::Event& events)
{
	for (auto& it : m_Components)
	{
		it->handle(target, events);
	}
}

void Container::tick(sf::RenderWindow& target, float32 dt)
{
	for (auto& it : m_Components)
	{
		it->tick(target, dt);
	}
}

void Container::render(sf::RenderTarget& target, sf::RenderStates& state)
{
	for (auto& it : m_Components)
	{
		it->render(target, state);
	}
}

void Container::add(Component::Pointer component)
{
	assert(component != nullptr);
	if (component != nullptr)
	{
		m_Components.emplace_back(component);
	}
	else
	{
		Singletons::log.print(Singletons::resources.findString("GUI_CONTAINER_NULLPTR"));
		throw Error::Fatal;
	}
}
