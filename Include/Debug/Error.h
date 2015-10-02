#ifndef ERROR_H
#define ERROR_H

#include <string>

namespace Grim
{
	class Engine;

	class Error
	{
	public:
		enum Type
		{
			Fatal,
			Divide_By_Zero,
			Out_Of_Range,
		};

		static void handle(Error::Type error, Engine& engine);
		static void handleXMLParse();
		static void changeSFMLrdbuff();
		static const std::string convertSFML();
	public:
		static std::ostringstream sfErrorStream;
	};
}

#endif