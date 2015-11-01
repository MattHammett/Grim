#include "Strings.h"
#include "../Utility/File.h"
#include "../Debug/Error.h"
#include "../Utility/Singletons.h"
#include <sstream>
#include <iostream>
using namespace Grim;

xml_document<> Strings::m_Document;
std::map<std::string, std::string> Strings::m_Strings;

void Strings::initialize()
{
	initializeAllStrings();
}

void Strings::terminate()
{
	m_Strings.clear();
}

const std::string& Strings::find(const std::string & name)
{
	// Check if name exsists
	auto found = m_Strings.find(name);
	bool exists = (found != m_Strings.end());

	assert(exists);
	if (exists)
	{
		return m_Strings[name];
	}
	else
	{
		Singletons::log.preInitializePrint(Log::Level::Fatal, Singletons::resources.findString("STRINGS_FIND_ERROR"));
		return Singletons::resources.findString("STRINGS_DEFAULT_STRING");
	}
}

void Strings::initializeAllStrings()
{
	// Load XML file to string and parse it
	std::ifstream file("../Resource/Strings/Strings.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string xml(buffer.str());
	m_Document.parse<0>(&xml[0]);

	xml_node<>* strings = m_Document.first_node("strings");

	for (xml_node<>* stringNode = strings->first_node("string"); stringNode; stringNode = stringNode->next_sibling())
	{
		if (stringNode->value() != nullptr)
		{
			m_Strings.emplace(stringNode->first_attribute("name")->value(), stringNode->first_attribute("data")->value());
		}
	}
	m_Document.clear();
}