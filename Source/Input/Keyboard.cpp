#include "../../Include/Input/Keyboard.h"
#include "../../Include/Utility/Type.h"
#include <assert.h>
using namespace Grim;

std::map<Keyboard::Key, sf::Keyboard::Key> Keyboard::m_Keybinds;
std::map<Keyboard::Key, bool> Keyboard::m_Keystate;

void Keyboard::initialize()
{
	resetStates();

	m_Keybinds[Keyboard::Key::MoveUp]		= sf::Keyboard::W;
	m_Keybinds[Keyboard::Key::MoveDown]		= sf::Keyboard::S;
	m_Keybinds[Keyboard::Key::MoveLeft]		= sf::Keyboard::A;
	m_Keybinds[Keyboard::Key::MoveRight]	= sf::Keyboard::D;
	m_Keybinds[Keyboard::Key::Sprint]		= sf::Keyboard::LShift;
	m_Keybinds[Keyboard::Key::Escape]		= sf::Keyboard::Escape;
	m_Keybinds[Keyboard::Key::Jump]			= sf::Keyboard::Space;
}

void Keyboard::setBind(Keyboard::Key key, sf::Keyboard::Key newkey)
{
	m_Keybinds[key] = newkey;
}

bool Keyboard::isDown(Keyboard::Key key)
{
	assert(key > 0);
	assert(key < Keyboard::Key::TOTAL);
	return m_Keystate[key];
}

void Keyboard::resetStates()
{
	m_Keystate[Keyboard::Key::MoveUp]		= false;
	m_Keystate[Keyboard::Key::MoveDown]		= false;
	m_Keystate[Keyboard::Key::MoveLeft]		= false;
	m_Keystate[Keyboard::Key::MoveRight]	= false;
	m_Keystate[Keyboard::Key::Sprint]		= false;
	m_Keystate[Keyboard::Key::Escape]		= false;
	m_Keystate[Keyboard::Key::Jump]			= false;

	/*for (std::size_t i = 0; i < Keyboard::Key::TOTAL; ++i)
	{
		m_Keystate[static_cast<Keyboard::Key>(i)] = false;
	}*/
}

void Keyboard::checkStates()
{
	if (sf::Keyboard::isKeyPressed(m_Keybinds[Keyboard::Key::MoveUp]))		m_Keystate[Keyboard::Key::MoveUp]		= true;
	if (sf::Keyboard::isKeyPressed(m_Keybinds[Keyboard::Key::MoveDown]))	m_Keystate[Keyboard::Key::MoveDown]		= true;
	if (sf::Keyboard::isKeyPressed(m_Keybinds[Keyboard::Key::MoveLeft]))	m_Keystate[Keyboard::Key::MoveLeft]		= true;
	if (sf::Keyboard::isKeyPressed(m_Keybinds[Keyboard::Key::MoveRight]))	m_Keystate[Keyboard::Key::MoveRight]	= true;
	if (sf::Keyboard::isKeyPressed(m_Keybinds[Keyboard::Key::Sprint]))		m_Keystate[Keyboard::Key::Sprint]		= true;
	if (sf::Keyboard::isKeyPressed(m_Keybinds[Keyboard::Key::Escape]))		m_Keystate[Keyboard::Key::Escape]		= true;
	if (sf::Keyboard::isKeyPressed(m_Keybinds[Keyboard::Key::Jump]))		m_Keystate[Keyboard::Key::Jump]			= true;
}
