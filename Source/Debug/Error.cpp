#include "../../Include/Debug/Error.h"
#include "../../Include/Engine.h"
#include "../../Include/Utility/Singletons.h"
#include "../../Include/Setup.h"
#include <SFML\System\Err.hpp>
#include <iostream>
#include <sstream>
using namespace Grim;

std::ostringstream Error::sfErrorStream;

void Error::handle(Error::Type error, Engine& engine)
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

void Error::handleXMLParse()
{
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
