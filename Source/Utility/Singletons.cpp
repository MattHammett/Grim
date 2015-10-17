#include "../../Include/Utility/Singletons.h"
#include "../../Include/Debug/Log.h"
#include "../../Include/Utility/Time/Clock.h"
#include "../../Include/Lua/Lua.h"
#include "../../Include/Resource/Resources.h"
#include "../../Include/Game/GUI/DesktopManager.h"
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
