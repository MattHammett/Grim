#ifndef INPUT_H
#define INPUT_H

#include "../Utility/Singleton.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Grim
{
	class Singletons;

	class Input : public Singleton<Input>, public Keyboard, public Mouse
	{
		GRIM_SINGLETON
	public:
		void initialize() override;
		void terminate() override;

		bool isKeyDown(Keyboard::Key key);
		bool isMouseButtonDown(Mouse::Button button);

		void resetStates();
		void checkStates();
	};
}

#endif