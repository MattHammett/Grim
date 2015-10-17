#include "../../Include/Input/Mouse.h"
#include <assert.h>
using namespace Grim;

std::map<Mouse::Button, sf::Mouse::Button> Mouse::m_Mousebinds;
std::map<Mouse::Button, bool> Mouse::m_Mousestate;

void Mouse::initalize()
{
	m_Mousebinds[Mouse::Button::Left]	= sf::Mouse::Button::Left;
	m_Mousebinds[Mouse::Button::Right]	= sf::Mouse::Button::Right;

	checkStates();
}

void Mouse::setBind(Mouse::Button button, sf::Mouse::Button newbutton)
{
	m_Mousebinds[button] = newbutton;
}

bool Mouse::isDown(Mouse::Button button)
{
	assert(button >= 0);
	assert(button < Mouse::Button::TOTAL);
	return m_Mousestate[button];
}

void Mouse::checkStates()
{
	// Reset States
	for (std::size_t i = 0; i < Mouse::Button::TOTAL; ++i)
	{
		m_Mousestate[static_cast<Mouse::Button>(i)] = false;
	}

	// Check states
	for (std::size_t i = 0; i < Mouse::Button::TOTAL; ++i)
	{
		if (sf::Mouse::isButtonPressed(m_Mousebinds[static_cast<Mouse::Button>(i)]))
		{
			m_Mousestate[static_cast<Mouse::Button>(i)] = true;
		}
	}
}