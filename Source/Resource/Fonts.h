#ifndef FONTS_H
#define FONTS_H

#include <SFML\Graphics\Font.hpp>
#include <map>
#include <string>
#include <rapidxml.hpp>
using namespace rapidxml;

namespace Grim
{
	class Fonts
	{
	public:
		static void initialize();
		static void terminate();

		static const sf::Font& find(const std::string& name);
	private:
		explicit Fonts();
		static void initializeAllFonts();
	private:
		static xml_document<> m_Document;
		static std::map<std::string, sf::Font> m_Fonts;
	};
}

#endif