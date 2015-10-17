#include "../../Include/Lua/Lua.h"
#include "../../Include/Utility/Singletons.h"
#include <lualib.h>
#include <lauxlib.h>
using namespace Grim;

int32 test(lua_State* L)
{
	Singletons::log.print(Log::Level::Lua, "test");
	return 0;
}

void Lua::initialize()
{
	m_State = luaL_newstate();
	luaL_openlibs(m_State);

	lua_register(m_State, "test", test);

	Singletons::log.print(Log::Level::Verbose, Singletons::resources.findString("LUA_INITIALIZED"));
}

void Lua::terminate()
{
	lua_close(m_State);
	Singletons::log.print(Log::Level::Verbose, Singletons::resources.findString("LUA_TERMINATED"));
}

void Lua::testFunction()
{
	if (luaL_dofile(m_State, Singletons::resources.findString("LUA_SCRIPTS_TESTING_TEST_PATH").c_str()))
	{
		Singletons::log.print(Log::Lua, lua_tostring(m_State, LUA_STACK_TOP_INDEX));
		lua_pop(m_State, 1);
	}
}
