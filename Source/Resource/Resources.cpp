#include "../../Include/Resource/Resources.h"
using namespace Grim;

void Resources::initialize()
{
	Strings::initialize();
	Textures::initialize();
}

void Resources::terminate()
{
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
