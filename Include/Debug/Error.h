#ifndef ERROR_H
#define ERROR_H

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

		static void handleError(Error::Type error, Engine& engine);
	};
}

#endif