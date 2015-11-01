#ifndef HANDLE_H
#define HANDLE_H

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>

namespace Grim
{
	class Handle
	{
	public:
		virtual void handle(sf::RenderWindow& target, sf::Event& events) = 0;
	};
}

#endif

//void handle(sf::RenderWindow& target, sf::Event& events) override;
//void update(sf::RenderWindow& target, float32 dt) override;
//void render(sf::RenderTarget& target, sf::RenderStates& state) override;
