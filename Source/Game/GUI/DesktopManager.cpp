#include "../../../Include/Game/GUI/DesktopManager.h"
#include "../../../Include/Utility/Singletons.h"
using namespace Grim;

void DesktopManager::initialize()
{
	Singletons::log.print(Log::Level::Verbose, Singletons::resources.findString("GUI_INITIALIZED"));
}

void DesktopManager::terminate()
{
	Singletons::log.print(Log::Level::Verbose, Singletons::resources.findString("GUI_TERMINATED"));
}