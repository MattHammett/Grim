#include "Singletons.h"
#include "../Debug/Log.h"
#include "../Utility/Time/Clock.h"
#include "../Lua/Lua.h"
#include "../Resource/Resources.h"
#include "../Game/GUI/DesktopManager.h"
using namespace Grim;

Log& Singletons::log = Log::instance();
Clock& Singletons::clock = Clock::instance();
Lua& Singletons::lua = Lua::instance();
Input& Singletons::input = Input::instance();
Resources& Singletons::resources = Resources::instance();
DesktopManager& Singletons::gui = DesktopManager::instance();

void Singletons::initialize()
{
	clock.initialize();
	resources.initialize();
	log.initialize();
	lua.initialize();
	input.initialize();
	gui.initialize();

	log.print(Singletons::resources.findString("ENGINE_SINGLETONS_INITIALIZATION_SUCCESS"));
}

void Singletons::terminate()
{
	log.print(Singletons::resources.findString("ENGINE_SINGLETONS_TERMINATING"));

	gui.terminate();
	input.terminate();
	lua.terminate();
	clock.terminate();
	resources.terminate();
	log.terminate();
}
