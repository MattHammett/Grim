#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include "../../Utility/Type.h"

namespace Grim
{
	class Entity : public sf::Drawable, public sf::Transformable
	{
	public:
		virtual void update(sf::RenderWindow& target, float32 dt) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	protected:
		Vector2f m_Speed;
		Vector2f m_Velocity;
		Vector2f m_Acceleration;
		Vector2f m_FrictionTemp;
		Vector2f m_Direction;
	};
}

#endif