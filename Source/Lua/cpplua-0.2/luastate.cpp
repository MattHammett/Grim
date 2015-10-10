/***************************************************************************
 *   Copyright (C) 2004 by Paolo Capriotti                                 *
 *   p.capriotti@sns.it                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <cassert>
#include "../../../Include/Lua/cpplua-0.2/luastate.h"
#include "../../../Include/Lua/cpplua-0.2/luaobject.h"
#include "../../../Include/Lua/cpplua-0.2/luatable.h"
#include "../../../Include/Lua/cpplua-0.2/luafunction.h"
using namespace std;

namespace cpplua {

void LuaState::init() {
  // this table stays at the bottom of lua stack
  lua_newtable(L);
  cppluaTableIndex = lua_gettop(L);
  
  // initialize global table
  {
    LuaObject table(this);
    lua_pushlightuserdata(L, &table);
    lua_pushvalue(L, LUA_RIDX_GLOBALS);
    lua_settable(L, cppluaTableIndex);
    globalTable = new LuaTable(table);
  }
}

LuaState::LuaState() : collectState(true) {
  L = luaL_newstate();

  openBase();
  openIO();
  openTable();
  openString();
  openMath();
  
  init();
}

LuaState::~LuaState() {
  // empty cpplua table
  lua_pushnil(L);
  while (lua_next(L, cppluaTableIndex) != 0) {
    LuaObject* obj = static_cast<LuaObject*>(lua_touserdata(L, -2));
    delete obj;
    lua_pop(L, 1);
  }
  
  lua_pop(L, 1); // pop cppluaTableIndex

  if (collectState)
    lua_close(L);
}

LuaState::LuaState(lua_State* L) : L(L), collectState(false) {
  init();
}

void LuaState::openBase() {
  luaopen_base(L);
}

void LuaState::openIO() {
  luaopen_io(L);
}


void LuaState::openTable() {
  luaopen_table(L);
}


void LuaState::openString() {
  luaopen_string(L);
}


void LuaState::openMath() {
  luaopen_math(L);
}

string LuaState::getString(const LuaObject* obj) {
  pushEntry(obj);
  string res = lua_tostring(L, -1);
  lua_pop(L, 1);
  return res;
}

void LuaState::setString(const LuaObject* obj, const char* s) {
  lua_pushlightuserdata(L, (void*)obj);
  lua_pushstring(L, s);
  lua_settable(L, cppluaTableIndex);
}

int LuaState::getNumber(const LuaObject* obj) {
  pushEntry(obj);
  int res = static_cast<int>(lua_tonumber(L, -1));
  lua_pop(L, 1);
  return res;
}

void LuaState::setNumber(const LuaObject* obj, int n) {
  lua_pushlightuserdata(L, (void*)obj);
  lua_pushnumber(L, n);
  lua_settable(L, cppluaTableIndex);
}

void LuaState::setTableElement(const LuaObject* obj, const LuaTableElement& el) {
  lua_pushlightuserdata(L, (void*)obj);
  pushEntry(&(el.getTable()));
  pushEntry(&(el.getKey()));
  lua_gettable(L, -2);
  lua_remove(L, -2);
  lua_settable(L, cppluaTableIndex);
}

void LuaState::setTableElementValue(const LuaTable* tbl, const LuaObject* key, const LuaObject* value) {
  pushEntry(tbl);
  pushEntry(key);
  pushEntry(value);
  lua_settable(L, -3);
  lua_pop(L, 1);
}

void LuaState::call(const LuaObject* obj, int argc, int nReturn) {
  //  cerr << "inside call: argc = " << argc << " nReturn = " << nReturn << " obj = " << obj << " top = " << top() << endl;
  int fIndex = lua_gettop(L) - argc + 1;
  pushEntry(obj);
  lua_insert(L, fIndex);
  if (!lua_isfunction(L, fIndex)) {
    cerr << "bug: " << obj << " is not a function" << endl;
    cerr << "\tIt's type is: " << lua_typename(L, lua_type(L, fIndex)) << endl;
  }
  if (lua_pcall(L, argc, nReturn, 0))
    throw LuaRuntimeError(lua_tostring(L, -1));
}

bool LuaState::equal(const LuaObject* obj1, const LuaObject* obj2) {
  pushEntry(obj1);
  pushEntry(obj2);
  bool res = lua_rawequal(L, -1, -2);
  lua_pop(L, 2);
  return res;
}

/*LuaObject LuaState::getTableElement(const LuaTableElement& el) {
  LuaObject res(this);
  lua_pushlightuserdata(L, &res);
  
  pushEntry(el->getTable());
  pushEntry(el->getKey());
  lua_gettable(L, -2);
  
  lua_settable(L, cppluaTableIndex);
  return res;
  }*/

void LuaState::pushEntry(const LuaObject* obj) {
  lua_pushlightuserdata(L, (void*)obj);
  lua_gettable(L, cppluaTableIndex);
}

LuaObject LuaState::popEntry(int n) {
  LuaObject res;
  if (n > 0) {
    lua_pushlightuserdata(L, &res);
    lua_insert(L, -2);
    lua_settable(L, cppluaTableIndex);
    lua_pop(L, n-1);
  }
  return res;
}

int LuaState::next(const LuaTable* table, const LuaObject* key) {
  pushEntry(table);
  pushEntry(key);
  int res = lua_next(L, -2);
  lua_pop(L, 1); // discard value
  lua_remove(L, -2); // discard table
  return res; // leaving next key on the stack
  /* Note: this function keeps the stack untouched if key is at the end */
}

void LuaState::duplicateEntry(LuaObject* obj1, const LuaObject* obj2) {
  lua_pushlightuserdata(L, obj1);
  pushEntry(obj2);
  lua_settable(L, cppluaTableIndex);
}

void LuaState::removeEntry(LuaObject* obj) {
  lua_pushlightuserdata(L, obj);
  lua_pushnil(L);
  lua_settable(L, cppluaTableIndex);
}

int LuaState::generalFunction(lua_State* state) {
  int (*f)(LuaState*) = reinterpret_cast<int(*)(LuaState*)>
    (lua_tocfunction(state, lua_upvalueindex(1)));
  LuaState tempState(state);
  return f(&tempState);
}

LuaFunction LuaState::createFunction(cppluaFunction* f) {
  LuaObject res;
  lua_pushlightuserdata(L, &res);
  lua_pushcfunction(L, reinterpret_cast<cluaFunction*>(f));
  lua_pushcclosure(L, LuaState::generalFunction, 1);
  lua_settable(L, cppluaTableIndex);
  return res;
}

LuaFunction LuaState::createFunctionFromObject() {
  LuaObject res(this);
  return LuaFunction(res);
}

// -----

#define CHECK_TYPE(fname, type) \
  bool LuaState:: fname (const LuaObject* obj) { \
    pushEntry(obj); \
    bool res = type (L, -1); \
    lua_pop(L, 1); \
    return res; \
  }

CHECK_TYPE(isNumber, lua_isnumber)
  CHECK_TYPE(isString, lua_isstring)
  CHECK_TYPE(isFunction, lua_isfunction)
  CHECK_TYPE(isTable, lua_istable)

string LuaState::typeName(const LuaObject* obj) {
  pushEntry(obj);
  string res(lua_typename(L, lua_type(L, -1)));
  lua_pop(L, 1);
  return res;
}

LuaState::LuaType LuaState::getType(const LuaObject* obj) {
  pushEntry(obj);
  LuaType res = static_cast<LuaType>(lua_type(L, -1));
  lua_pop(L, 1);
  return res;
}


/**
   Get a global object
*/
/*LuaObject LuaState::operator[](const char* name) {
  LuaObject res(this);
  lua_pushlightuserdata(L, &res);
  lua_getglobal(L, name);
  lua_settable(L, cppluaTableIndex);
  return res;
  }*/

LuaTableElement LuaState::operator[](const LuaObject& key) {
  return LuaTableElement(*globalTable, key);
}

/**
   Load a lua file
*/
LuaFunction LuaState::loadFile(const char* filename) {
  LuaObject res(this);
  lua_pushlightuserdata(L, &res);
  
  if (luaL_loadfile(L, filename))
    throw LuaRuntimeError(lua_tostring(L, -1));
  
  lua_settable(L, cppluaTableIndex);
  return LuaFunction(res, 0);
}

/**
   Execute a lua script
*/
void LuaState::doFile(const char* filename) {
  LuaFunction executeScript = loadFile(filename);
  executeScript();
}

LuaObject LuaState::getNil() const {
  return LuaObject(const_cast<LuaState*>(this));
}

};
