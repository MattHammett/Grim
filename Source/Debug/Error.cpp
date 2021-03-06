#include "Error.h"
#include "../Engine.h"
#include "../Utility/Singletons.h"
#include "../Setup.h"
#include <SFML\System\Err.hpp>
#include <iostream>
#include <sstream>
using namespace Grim;

std::ostringstream Error::sfErrorStream;

void Error::handle(Error::Type error, Engine& engine)
{
	bool bAbort = false;

	assert(error >= 0);
	assert(error <= Error::Out_Of_Range);

	switch (error)
	{
	case Error::Fatal:
		Singletons::log.print(Log::Level::Info, Singletons::resources.findString("ENGINE_ERROR_FATAL"));
		bAbort = true;
		engine.exit();
		break;
	case Error::Divide_By_Zero:
		Singletons::log.print(Log::Level::Info, Singletons::resources.findString("ENGINE_ERROR_DIVIDE_BY_ZERO"));
		bAbort = true;
		engine.exit();
		break;
	case Error::Out_Of_Range:
		Singletons::log.print(Log::Level::Info, Singletons::resources.findString("ENGINE_ERROR_OUT_OF_RANGE"));
		bAbort = true;
		engine.exit();
		break;
	}
	if (bAbort)
	{
		Singletons::log.print(Log::Level::Info, Singletons::resources.findString("ENGINE_ABORTED"));
		engine.setExitCode(GRIM_EXIT_FAILURE);
	}
}

void Error::handleXMLParse()
{
	// Have to use console output since the error is within the strings singleton
	std::cout << "Error: XML parse error. File corrupt or syntax error!" << std::endl;
	std::cin.sync();
	std::cin.ignore();
}

void Error::changeSFMLrdbuff()
{
	sf::err().rdbuf(sfErrorStream.rdbuf());
}

const std::string Error::convertSFML()
{
	std::string error = sfErrorStream.str();
	if (error.size() != 0)
	{
		error.pop_back();
		return error;
	}
	return std::string();
}
