#ifndef SINGLETONS_H
#define SINGLETONS_H

#include "../Debug/Log.h"
#include "../Utility/Time/Clock.h"
#include "../Lua/Lua.h"
#include "../Input/Input.h"
#include "../Resource/Resources.h"
#include "../Game/GUI/DesktopManager.h"

namespace Grim
{
	class Singletons
	{
		friend class Log;
		friend class Clock;
		friend class Lua;
		friend class Input;
		friend class Resources;
		friend class DesktopManager;
	public:
		static void initialize();
		static void terminate();

		static Log& log;
		static Clock& clock;
		static Lua& lua;
		static Input& input;
		static Resources& resources;
		static DesktopManager& gui;
	private:
		explicit Singletons();
	};
}

#endif