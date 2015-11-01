#include "Fonts.h"
#include "../Debug/Error.h"
#include "../Utility/Singletons.h"
#include <assert.h>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace Grim;

xml_document<> Fonts::m_Document;
std::map<std::string, sf::Font> Fonts::m_Fonts;

void Fonts::initialize()
{
	initializeAllFonts();
}

void Fonts::terminate()
{
	m_Fonts.clear();
}

const sf::Font& Grim::Fonts::find(const std::string& name)
{
	assert(name.size() > 0);
	bool bExists = (m_Fonts.count(name) > 0);
	assert(bExists);

	if (bExists)
	{
		return m_Fonts[name];
	}
	else
	{
		Singletons::log.preInitializePrint(Log::Level::Fatal, Singletons::resources.findString("FONT_NOT_FOUND"));
		throw ;
	}
}

void Fonts::initializeAllFonts()
{
	std::ifstream file(Singletons::resources.findString("FONT_PATHS"));
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string xml(buffer.str());
	m_Document.parse<0>(&xml[0]);

	xml_node<>* font = m_Document.first_node("fonts");

	for (xml_node<>* fontNode = font->first_node("font"); fontNode; fontNode = fontNode->next_sibling())
	{
		if (fontNode->value() != nullptr)
		{
			sf::Font fontTemp;
			fontTemp.loadFromFile(fontNode->first_attribute("data")->value());
			m_Fonts.emplace(fontNode->first_attribute("name")->value(), std::move(fontTemp));
		}
	}
	m_Document.clear();
}