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

bool Input::isKeyDown(Keyboard::Key key)
{
	return Keyboard::isDown(key);
}

bool Input::isMouseButtonDown(Mouse::Button button)
{
	return Mouse::isDown(button);
}

void Input::resetStates()
{
	Keyboard::resetStates();
	Mouse::resetStates();
}

void Input::checkStates()
{
	Keyboard::checkStates();
	Mouse::checkStates();
}