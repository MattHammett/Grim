#ifndef COMPONENT_H
#define COMPONENT_H

#include "../../Utility/Interfaces/Handle.h"
#include "../../Utility/Interfaces/Tick.h"
#include "../../Utility/Interfaces/Render.h"
#include <memory>

namespace Grim
{
	class Component : public Handle, public Tick, public Render
	{
	public:
		using Pointer = std::shared_ptr<Component>;
		using Vector = std::vector<Component::Pointer>;
	public:
		explicit Component();

		virtual void handle(sf::RenderWindow& target, sf::Event& events) = 0;
		virtual void tick(sf::RenderWindow& target, float32 dt) = 0;
		virtual void render(sf::RenderTarget& target, sf::RenderStates& state) = 0;

		void setParent(Component::Pointer parent);
	private:
		Component::Pointer m_Parent;
	};
}

#endif