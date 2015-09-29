#include "../Include/Singletons.h"
using namespace Grim;

Log& Singletons::log = Log::instance();

void Singletons::initialize()
{
	log.initialize();
}

void Singletons::terminate()
{
	log.terminate();
}
