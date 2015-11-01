#ifndef STRINGS_H
#define STRINGS_H

#include <map>
#include <rapidxml.hpp>
using namespace rapidxml;

namespace Grim
{
	class Strings
	{
	public:
		static void initialize();
		static void terminate();

		static const std::string& find(const std::string& name);
	private:
		explicit Strings();
		static void initializeAllStrings();
	private:
		static xml_document<> m_Document;
		static std::map<std::string, std::string> m_Strings;
	};
}

#endif