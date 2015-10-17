#include "../../Include/Input/Input.h"
using namespace Grim;

void Input::initialize()
{
	Keyboard::initialize();
	Mouse::initalize();
}

void Input::terminate()
{
}

bool Input::isKeybindDown(Keyboard::Key key)
{
	return Keyboard::isDown(key);
}

bool Input::isMousebindDown(Mouse::Button button)
{
	return Mouse::isDown(button);
}

void Input::checkStates()
{
	Keyboard::checkStates();
	Mouse::checkStates();
}