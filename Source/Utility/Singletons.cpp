#include "../../Include/Utility/Singletons.h"
#include "../../Include/Debug/Log.h"
#include "../../Include/Utility/Time/Clock.h"
#include "../../Include/Lua/Lua.h"
using namespace Grim;

Log& Singletons::log = Log::instance();
Clock& Singletons::clock = Clock::instance();
Strings& Singletons::strings = Strings::instance();
Lua& Singletons::lua = Lua::instance();
Input& Singletons::input = Input::instance();

void Singletons::initialize()
{
	clock.initialize();
	strings.initialize();
	log.initialize();
	lua.initialize();
	input.initialize();

	log.print(Singletons::strings.find("ENGINE_SINGLETONS_INITIALIZATION_SUCCESS"));
}

void Singletons::terminate()
{
	log.print(Singletons::strings.find("ENGINE_SINGLETONS_TERMINATING"));

	input.terminate();
	lua.terminate();
	strings.terminate();
	clock.terminate();
	log.terminate();
}
