#ifndef SINGLETONS_H
#define SINGLETONS_H

#include "../Debug/Log.h"
#include "../Utility/Time/Clock.h"
#include "../Resource/Strings.h"
#include "../Lua/Lua.h"

namespace Grim
{
	class Singletons
	{
		friend class Log;
		friend class Clock;
		friend class Strings;
		friend class Lua;
	public:
		static void initialize();
		static void terminate();

		static Log& log;
		static Clock& clock;
		static Strings& strings;
		static Lua& lua;
	private:
		explicit Singletons();
	};
}

#endif