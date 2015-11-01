#ifndef MOUSE_H
#define MOUSE_H

#include <SFML\Window\Mouse.hpp>
#include <map>

namespace Grim
{
	class Mouse
	{
	public:
		enum Button
		{
			Left,
			Right,
			TOTAL
		};
	protected:
		static void initalize();

		static void setBind(Mouse::Button button, sf::Mouse::Button newbutton);
		static bool isDown(Mouse::Button button);

		static void checkStates();
	private:
		static std::map<Mouse::Button, sf::Mouse::Button> m_Mousebinds;
		static std::map<Mouse::Button, bool> m_Mousestate;
	};
}

#endif