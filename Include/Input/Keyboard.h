#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>
#include <map>

namespace Grim
{
	class Keyboard
	{
	public:
		enum Key
		{
			MoveUp,
			MoveDown,
			MoveLeft,
			MoveRight,
			Sprint,
			Escape,
			Jump,
			TOTAL
		};
	protected:
		static void initialize();

		static void setBind(Keyboard::Key key, sf::Keyboard::Key newkey);
		static bool isDown(Keyboard::Key key);

		static void resetStates();
		static void checkStates();
	private:
		static std::map<Keyboard::Key, sf::Keyboard::Key> m_Keybinds;
		static std::map<Keyboard::Key, bool> m_Keystate;
	};

}

#endif