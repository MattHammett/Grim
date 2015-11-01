#ifndef DESKTOP_H
#define DESKTOP_H

#include "Component.h"
#include "../../Utility/Interfaces/Handle.h"
#include "../../Utility/Interfaces/Tick.h"
#include "../../Utility/Interfaces/Render.h"
#include <memory>
#include <vector>

namespace Grim
{
	class Desktop : public Handle, public Tick, public Render
	{
	public:
		using Pointer = std::shared_ptr<Desktop>;
		using Vector = std::vector<Desktop::Pointer>;
	public:
		explicit Desktop();

		void handle(sf::RenderWindow& target, sf::Event& events) override;
		void tick(sf::RenderWindow& target, float32 dt) override;
		void render(sf::RenderTarget& target, sf::RenderStates& state) override;

		void add(Component::Pointer component);
	private:
		Component::Vector m_Components;
	};
}

#endif