#include "Textures.h"
#include "../Utility/Singletons.h"
#include "../Debug/Error.h"
#include <assert.h>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace Grim;

xml_document<> Textures::m_Document;
std::map<std::string, sf::Texture> Textures::m_Textures;

void Textures::initialize()
{
	initializeAllTextures();
}

void Textures::terminate()
{
	m_Textures.clear();
}

const sf::Texture& Textures::find(const std::string& name)
{
	assert(name.size() > 0);
	bool exists = (m_Textures.count(name) > 0);
	assert(exists);

	if (exists)
	{
		return m_Textures[name];
	}
	else
	{
		Singletons::log.preInitializePrint(Log::Level::Fatal, Singletons::resources.findString("TEXTURE_NOT_FOUND"));
		throw Error::Fatal;
	}
}

void Textures::initializeAllTextures()
{
	std::ifstream file(Singletons::resources.findString("TEXTURE_PATHS"));
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string xml(buffer.str());
	m_Document.parse<0>(&xml[0]);

	xml_node<>* texture = m_Document.first_node("textures");

	for (xml_node<>* textureNode = texture->first_node("texture"); textureNode; textureNode = textureNode->next_sibling())
	{
		if (textureNode->value() != nullptr)
		{
			sf::Texture textureTemp;
			textureTemp.loadFromFile(textureNode->first_attribute("data")->value());
			m_Textures.emplace(textureNode->first_attribute("name")->value(), std::move(textureTemp));
		}
	}
	m_Document.clear();
}