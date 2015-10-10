#include "../../Include/Lua/LuaState.h"
#include "../../Include/Utility/Singletons.h"
using namespace Grim;

void LuaState::initialize()
{
	m_State = luaL_newstate();
	luaL_openlibs(m_State);

	if (luaL_dofile(m_State, Singletons::strings.find("LUA_SCRIPTS_TESTING_TEST_PATH").c_str()))
	{
		Singletons::log.print(Log::Error, lua_tostring(m_State, -1));
	}
}

void LuaState::terminate()
{
	lua_close(m_State);
}