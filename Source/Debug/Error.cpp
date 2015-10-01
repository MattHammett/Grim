#include "../../Include/Debug/Error.h"
#include "../../Include/Engine.h"
#include "../../Include/Utility/Singletons.h"
#include "../../Include/Setup.h"
#include <iostream>
using namespace Grim;

void Error::handleError(Error::Type error, Engine& engine)
{
	bool abort = false;

	assert(error >= 0);
	assert(error <= Error::Out_Of_Range);

	switch (error)
	{
	case Grim::Error::Fatal:
		Singletons::log.print(Log::Level::Info, Singletons::strings.find("ENGINE_ERROR_FATAL"));
		abort = true;
		engine.exit();
		break;
	case Grim::Error::Divide_By_Zero:
		Singletons::log.print(Log::Level::Info, Singletons::strings.find("ENGINE_ERROR_DIVIDE_BY_ZERO"));
		abort = true;
		engine.exit();
		break;
	case Grim::Error::Out_Of_Range:
		Singletons::log.print(Log::Level::Info, Singletons::strings.find("ENGINE_ERROR_OUT_OF_RANGE"));
		abort = true;
		engine.exit();
		break;
	}
	if (abort)
	{
		Singletons::log.print(Log::Level::Info, Singletons::strings.find("ENGINE_ABORTED"));
		engine.setExitCode(GRIM_EXIT_FAILURE);
	}
}
