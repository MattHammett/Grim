#include "../../Include/Utility/Singletons.h"
#include "../../Include/Debug/Log.h"
#include "../../Include/Utility/Time/Clock.h"
using namespace Grim;

Log& Singletons::log = Log::instance();
Clock& Singletons::clock = Clock::instance();
Strings& Singletons::strings = Strings::instance();

void Singletons::initialize()
{
	strings.initialize();
	log.initialize();
	clock.initialize();

	log.print(Singletons::strings.find("ENGINE_SINGLETONS_INITIALIZATION_SUCCESS"));
}

void Singletons::terminate()
{
	log.print(Singletons::strings.find("ENGINE_SINGLETONS_TERMINATING"));

	strings.terminate();
	clock.terminate();
	log.terminate();
}
