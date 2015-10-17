#ifndef RESOURCES_H
#define RESOURCES_H

#include "../Utility/Singleton.h"
#include "Textures.h"
#include "Strings.h"

namespace Grim
{
	class Singletons;

	class Resources : public Singleton<Resources>
	{
		GRIM_SINGLETON
	public:
		void initialize() override;
		void terminate() override;

		const sf::Texture& findTexture(const std::string& texture);
		const std::string& findString(const std::string& string);
		//const sf::Font& findFont(const std::string& font);
	};
}

#endif