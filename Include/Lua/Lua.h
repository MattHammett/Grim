#ifndef LUA_STATE_H
#define LUA_STATE_H

#include "../Utility/Singleton.h"
#include "../Utility/Type.h"
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include <string>

#define LUA_STACK_TOP_INDEX -1

namespace Grim
{
	class Singletons;

	class Lua : public Singleton<Lua>
	{
		GRIM_SINGLETON
	public:
		void initialize() override;
		void terminate() override;

		void testFunction();
	private:
		lua_State* m_State;
	};
}

#endif