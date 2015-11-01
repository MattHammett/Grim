#ifndef UPDATE_H
#define UPDATE_H

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include "../Type.h"

namespace Grim
{
	class Tick
	{
	public:
		virtual void tick(sf::RenderWindow& target, float32 dt) = 0;
	};
}

#endif