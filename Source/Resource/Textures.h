#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML\Graphics\Texture.hpp>
#include <map>
#include <string>
#include <rapidxml.hpp>
using namespace rapidxml;

namespace Grim
{
	class Textures
	{
	public:
		static void initialize();
		static void terminate();

		static const sf::Texture& find(const std::string& name);
	private:
		explicit Textures();
		static void initializeAllTextures();
	private:
		static xml_document<> m_Document;
		static std::map<std::string, sf::Texture> m_Textures;
	};
}

#endif