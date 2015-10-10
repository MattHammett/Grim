#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <exception>

#define RAPIDXML_PARSE_ERROR(what, where) throw parse_error(what, where)

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


	////! Parse error exception. 
	////! This exception is thrown by the parser when an error occurs. 
	////! Use what() function to get human-readable error message. 
	////! Use where() function to get a pointer to position within source text where error was detected.
	////! <br><br>
	////! If throwing exceptions by the parser is undesirable, 
	////! it can be disabled by defining RAPIDXML_NO_EXCEPTIONS macro before rapidxml.hpp is included.
	////! This will cause the parser to call rapidxml::parse_error_handler() function instead of throwing an exception.
	////! This function must be defined by the user.
	////! <br><br>
	////! This class derives from <code>std::exception</code> class.

	//class ErrorFatal : public std::exception
	//{
	//public:
	//	ErrorFatal(const char* what, void* where)
	//		: m_What(what)
	//		, m_Where(where)
	//	{
	//	}

	//	const char* what() const throw() override
	//	{
	//		return m_What;
	//	}

	//	template<class Ch>
	//	Ch* where() const
	//	{
	//		return reinterpret_cast<Ch*>(m_Where);
	//	}
	//private:
	//	const char *m_What;
	//	void *m_Where;
	//};
}

#endif