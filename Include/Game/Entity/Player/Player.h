#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity.h"
#include "PlayerController.h"
#include <SFML\Graphics\RectangleShape.hpp>

namespace Grim
{
	class Player : public Entity
	{
	public:
		enum State
		{
			Idle,
			Walking,
			Sprinting
		};
	public:
		explicit Player();

		void update(sf::RenderWindow& target, float32 dt) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		void applyFriction();
	private:
		sf::RectangleShape m_Shape;
		PlayerController m_Controller;
		Player::State m_StateCurrent;
	};
}

#endif