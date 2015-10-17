#include "../../Include/Input/Keyboard.h"
#include "../../Include/Utility/Type.h"
#include <assert.h>
using namespace Grim;

std::map<Keyboard::Key, sf::Keyboard::Key> Keyboard::m_Keybinds;
std::map<Keyboard::Key, bool> Keyboard::m_Keystate;

void Keyboard::initialize()
{
	m_Keybinds[Keyboard::Key::MoveUp]		= sf::Keyboard::W;
	m_Keybinds[Keyboard::Key::MoveDown]		= sf::Keyboard::S;
	m_Keybinds[Keyboard::Key::MoveLeft]		= sf::Keyboard::A;
	m_Keybinds[Keyboard::Key::MoveRight]	= sf::Keyboard::D;
	m_Keybinds[Keyboard::Key::Sprint]		= sf::Keyboard::LShift;
	m_Keybinds[Keyboard::Key::Escape]		= sf::Keyboard::Escape;
	m_Keybinds[Keyboard::Key::Jump]			= sf::Keyboard::Space;

	checkStates();
}

void Keyboard::setBind(Keyboard::Key key, sf::Keyboard::Key newkey)
{
	m_Keybinds[key] = newkey;
}

bool Keyboard::isDown(Keyboard::Key key)
{
	assert(key >= 0);
	assert(key < Keyboard::Key::TOTAL);
	return m_Keystate[key];
}

void Keyboard::checkStates()
{
	// Reset states
	for (std::size_t i = 0; i < Keyboard::Key::TOTAL; ++i)
	{
		m_Keystate[static_cast<Keyboard::Key>(i)] = false;
	}

	// Check states
	for (std::size_t i = 0; i < Keyboard::Key::TOTAL; ++i)
	{
		if (sf::Keyboard::isKeyPressed(m_Keybinds[static_cast<Keyboard::Key>(i)]))
		{
			m_Keystate[static_cast<Keyboard::Key>(i)] = true;
		}
	}
}
