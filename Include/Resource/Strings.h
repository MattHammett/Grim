#ifndef STRINGS_H
#define STRINGS_H

#include "../Utility/Singleton.h"
#include <map>
#include <rapidxml.hpp>
using namespace rapidxml;

namespace Grim
{
	class Singletons;

	class Strings : public Singleton<Strings>
	{
		GRIM_SINGLETON
	public:
		void initialize() override;
		void terminate() override;

		const std::string& find(const std::string& name);
	private:
		void initializeAllStrings();
	private:
		xml_document<> m_Document;
		std::map<std::string, std::string> m_Strings;
	};
}

#endif