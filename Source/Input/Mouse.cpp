#include "../../Include/Input/Mouse.h"
#include <assert.h>
using namespace Grim;

std::map<Mouse::Button, sf::Mouse::Button> Mouse::m_Mousebinds;
std::map<Mouse::Button, bool> Mouse::m_Mousestate;

void Mouse::initalize()
{
	resetStates();

	m_Mousebinds[Mouse::Button::Left]	= sf::Mouse::Button::Left;
	m_Mousebinds[Mouse::Button::Right]	= sf::Mouse::Button::Right;
}

void Mouse::setBind(Mouse::Button button, sf::Mouse::Button newbutton)
{
	m_Mousebinds[button] = newbutton;
}

bool Mouse::isDown(Mouse::Button button)
{
	assert(button > 0);
	assert(button < Mouse::Button::TOTAL);
	return m_Mousestate[button];
}

void Mouse::resetStates()
{
	m_Mousestate[Mouse::Button::Left]	 = false;
	m_Mousestate[Mouse::Button::Right]	 = false;
}

void Mouse::checkStates()
{
	if (sf::Mouse::isButtonPressed(m_Mousebinds[Mouse::Button::Left]))		m_Mousestate[Mouse::Button::Left]		= true;
	if (sf::Mouse::isButtonPressed(m_Mousebinds[Mouse::Button::Right]))		m_Mousestate[Mouse::Button::Right]		= true;
}