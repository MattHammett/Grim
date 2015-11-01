#ifndef RENDER_H
#define RENDER_H

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

namespace Grim
{
	class Render
	{
	public:
		virtual void render(sf::RenderTarget& target, sf::RenderStates& state) = 0;
	};
}

#endif