#ifndef CONTAINER_H
#define CONTAINER_H

#include "Component.h"
#include <vector>

namespace Grim
{
	class Container : public Component
	{
	public:
		explicit Container();

		void handle(sf::RenderWindow& target, sf::Event& events) override;
		void tick(sf::RenderWindow& target, float32 dt) override;
		void render(sf::RenderTarget& target, sf::RenderStates& state) override;

		void add(Component::Pointer component);
	private:
		Component::Vector m_Components;
	};
}

#endif