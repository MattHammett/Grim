#include "../../../../Include/Game/Entity/Player/Player.h"
#include "../../../../Include/Utility/Math/Constants.h"
#include "../../../../Include/Utility/Math/Interpolation.h"
#include <SFML\Window\Keyboard.hpp>
using namespace Grim;

Player::Player()
{
	m_Controller = { false };
	m_StateCurrent = Player::State::Idle;
	m_Shape.setSize(Vector2f(32.0f, 64.0f));

	m_Speed = Vector2f(3.0f, 3.0f);
	m_Acceleration = Vector2f(10.0f, 10.0f);
	m_FrictionTemp = Vector2f(60.0f, 60.0f);
}

void Player::update(sf::RenderWindow& target, float32 dt)
{
	// Buggy movement needs fixing

	m_Controller = { false };
	//m_Direction = Vector2f(0.0f, 0.0f);
	bool diagonal = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_Controller.moveUp = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_Controller.moveDown = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_Controller.moveLeft = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_Controller.moveRight = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift))
	{
		m_Controller.sprint = true;
	}

	if (m_Controller.moveUp)
	{
		m_Direction.y = -1.0f; // Up
	}
	if (m_Controller.moveDown)
	{
		m_Direction.y = 1.0f; // Down
	}
	if (m_Controller.moveLeft)
	{
		m_Direction.x = -1.0f; // Left
	}
	if (m_Controller.moveRight)
	{
		m_Direction.x = 1.0f; // Right
	}

	// Check for diagonal
	if (m_Controller.moveUp && m_Controller.moveLeft)
	{
		diagonal = true;
	}
	if (m_Controller.moveLeft && m_Controller.moveDown)
	{
		diagonal = true;
	}
	if (m_Controller.moveDown && m_Controller.moveRight)
	{
		diagonal = true;
	}
	if (m_Controller.moveRight && m_Controller.moveUp)
	{
		diagonal = true;
	}

	if (!m_Controller.moveUp && !m_Controller.moveDown)
	{
		if (m_Velocity.y < 0.01f && m_Velocity.y > -0.01f)
		{
			m_Velocity.y = 0.0f;
		}
		else
		{
			m_Velocity.y = linearInterpolate(m_Velocity.y, 0.0f, m_FrictionTemp.y * (dt * dt));
		}
	}
	else
	{
		if (diagonal)
		{
			//float32 diagonalAccelerationY(m_Acceleration.y * GRIM_HALF_ROOT2);
			float32 diagonalSpeedY(m_Speed.y);

			if (m_Direction.y == -1.0f)
			{
				if (m_Velocity.y < diagonalSpeedY * m_Direction.y)
				{
					m_Velocity.y = diagonalSpeedY * m_Direction.y;
				}
				else
				{
					m_Velocity.y += m_Acceleration.y * m_Direction.y * dt;
				}
			}
			else
			{
				if (m_Velocity.y > diagonalSpeedY * m_Direction.y)
				{
					m_Velocity.y = diagonalSpeedY * m_Direction.y;
				}
				else
				{
					m_Velocity.y += m_Acceleration.y * m_Direction.y * dt;
				}
			}
		}
		else // Not diagonal
		{
			if (m_Direction.y == -1.0f)
			{
				if (m_Velocity.y < m_Speed.y * m_Direction.y)
				{
					m_Velocity.y = m_Speed.y * m_Direction.y;
				}
				else
				{
					m_Velocity.y += m_Acceleration.y * m_Direction.y * dt;
				}
			}
			else
			{
				if (m_Velocity.y > m_Speed.y * m_Direction.y)
				{
					m_Velocity.y = m_Speed.y * m_Direction.y;
				}
				else
				{
					m_Velocity.y += m_Acceleration.y * m_Direction.y * dt;
				}
			}
		}
	}

	if (!m_Controller.moveLeft && !m_Controller.moveRight)
	{
		if (m_Velocity.x < 0.01f && m_Velocity.x > -0.01f)
		{
			m_Velocity.x = 0.0f;
		}
		else
		{
			m_Velocity.x = linearInterpolate(m_Velocity.x, 0.0f, m_FrictionTemp.x * (dt * dt));
		}
	}
	else
	{
		if (diagonal)
		{
			//float32 diagonalAccelerationX(m_Acceleration.x * GRIM_HALF_ROOT2);
			float32 diagonalSpeedX(m_Speed.x);
			
			if (m_Direction.x == -1.0f)
			{
				if (m_Velocity.x < diagonalSpeedX * m_Direction.x)
				{
					m_Velocity.x = diagonalSpeedX * m_Direction.x;
				}
				else
				{
					m_Velocity.x += m_Acceleration.x * m_Direction.x * dt;
				}
			}
			else
			{
				if (m_Velocity.x > diagonalSpeedX * m_Direction.x)
				{
					m_Velocity.x = diagonalSpeedX * m_Direction.x;
				}
				else
				{
					m_Velocity.x += m_Acceleration.x * m_Direction.x * dt;
				}
			}
		}
		else // Not diagonal
		{
			if (m_Direction.x == -1.0f)
			{
				if (m_Velocity.x < m_Speed.x * m_Direction.x)
				{
					m_Velocity.x = m_Speed.x * m_Direction.x;
				}
				else
				{
					m_Velocity.x += m_Acceleration.x * m_Direction.x * dt;
				}
			}
			else
			{
				if (m_Velocity.x > m_Speed.x * m_Direction.x)
				{
					m_Velocity.x = m_Speed.x * m_Direction.x;
				}
				else
				{
					m_Velocity.x += m_Acceleration.x * m_Direction.x * dt;
				}
			}
		}
	}

	move(m_Velocity);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_Shape, states);
}

void Player::applyFriction()
{
	if (m_Velocity.x <= 0.0f)
	{
		m_Velocity.x = 0.0f;
	}
	if (m_Velocity.y <= 0.0f)
	{
		m_Velocity.y = 0.0f;
	}
	if (m_Velocity.x >= m_Speed.x)
	{
		m_Velocity.x = m_Speed.x;
	}
	if (m_Velocity.y >= m_Speed.y)
	{
		m_Velocity.y = m_Speed.y;
	}
}
