#include "../../Include/Input/Input.h"
#include "../../Include/Utility/Singletons.h"
using namespace Grim;

void Input::initialize()
{
	Keyboard::initialize();
	Mouse::initalize();

	Singletons::log.print(Log::Level::Verbose, Singletons::resources.findString("INPUT_INITIALIZED"));
}

void Input::terminate()
{
	Singletons::log.print(Log::Level::Verbose, Singletons::resources.findString("INPUT_TERMINATED"));
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