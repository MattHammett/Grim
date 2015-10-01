#include "../../Include/Resource/Strings.h"
#include "../../Include/Utility/File.h"
#include "../../Include/Debug/Error.h"
#include "../../Include/Utility/Singletons.h"
#include <sstream>
#include <iostream>
using namespace Grim;

void Strings::initialize()
{
	initializeAllStrings();
}

void Strings::terminate()
{
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
}