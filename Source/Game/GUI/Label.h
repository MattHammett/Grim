#ifndef LABEL_H
#define LABEL_H

#include "Component.h"
#include <SFML\Graphics\Text.hpp>

namespace Grim
{
	class Label : public Component
	{
	public:
		using Pointer = std::shared_ptr<Label>;
	public:
		explicit Label();

		void handle(sf::RenderWindow& target, sf::Event& events) override;
		void tick(sf::RenderWindow& target, float32 dt) override;
		void render(sf::RenderTarget& target, sf::RenderStates& state) override;
	private:
		sf::Text m_Text;
	};
}

#endif