#include "../../Include/Resource/Resources.h"
#include "../../Include/Utility/Singletons.h"
using namespace Grim;

void Resources::initialize()
{
	Strings::initialize();
	Textures::initialize();
	Singletons::log.preInitializePrint(Log::Level::Verbose, "RESOURCES_INITIALIZED");
}

void Resources::terminate()
{
	Singletons::log.print(Log::Level::Verbose, findString("RESOURCES_TERMINATED"));
	Textures::terminate();
	Strings::terminate();
}

const sf::Texture& Resources::findTexture(const std::string& texture)
{
	return Textures::find(texture);
}

const std::string& Resources::findString(const std::string& string)
{
	return Strings::find(string);
}
