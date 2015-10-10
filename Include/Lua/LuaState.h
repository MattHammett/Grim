#ifndef LUA_STATE_H
#define LUA_STATE_H

#include "../Utility/Singleton.h"
#include <lua.hpp>

namespace Grim
{
	class Singletons;

	class LuaState : public Singleton<LuaState>
	{
		GRIM_SINGLETON
	public:
		enum Type
		{
			Nil				= LUA_TNIL,
			Number			= LUA_TNUMBER,
			Boolean			= LUA_TBOOLEAN,
			String			= LUA_TSTRING,
			Table			= LUA_TTABLE,
			Function		= LUA_TFUNCTION,
			UserData		= LUA_TUSERDATA,
			Thread			= LUA_TTHREAD,
			LightUserData	= LUA_TLIGHTUSERDATA
		};
	public:
		void initialize() override;
		void terminate() override;
	private:
		lua_State* m_State;
	};
}

#endif