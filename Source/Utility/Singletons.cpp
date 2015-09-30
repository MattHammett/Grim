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
}

void Singletons::terminate()
{
	strings.terminate();
	clock.terminate();
	log.terminate();
}
