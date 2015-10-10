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
#ifndef LUASTATE_H
#define LUASTATE_H

#include <iostream>
#include <cstring>

#define STACK_COLLECTIBLE_DEBUG
#include "stackcollectible.h"

#include "common.h"

namespace cpplua {

class LuaObject;
class LuaTableElement;
class LuaState;

typedef int cppluaFunction(LuaState*);
typedef int cluaFunction(lua_State*);

stack_collectible_class(LuaState) {
public:
  enum LuaType {
    NilType = LUA_TNIL,
    NumberType = LUA_TNUMBER, 
    BooleanType = LUA_TBOOLEAN, 
    StringType = LUA_TSTRING,
    TableType = LUA_TTABLE, 
    FunctionType = LUA_TFUNCTION, 
    UserDataType = LUA_TUSERDATA,
    ThreadType = LUA_TTHREAD, 
    LightUserDataType = LUA_TLIGHTUSERDATA,
  };
private:
  lua_State* L;
  int cppluaTableIndex;
  bool collectState; /// whether L shall be destroyed
  
  void init();;
  
  DEFINE_ACCESSOR(LuaState, getCurrentState);

  friend class LuaObject;
  friend class LuaFunction;
  friend class LuaTable;
  
  void pushEntry(const LuaObject*);
  LuaObject popEntry(int n = 1);
  int next(const LuaTable* table, const LuaObject* key);
  void duplicateEntry(LuaObject*, const LuaObject*);
  void removeEntry(LuaObject*);
  LuaType getType(const LuaObject*);
  std::string getString(const LuaObject*);
  void setString(const LuaObject*, const char* s);
  int getNumber(const LuaObject*);
  void setNumber(const LuaObject*, int n);
  void call(const LuaObject*, int, int);
  bool equal(const LuaObject* obj1, const LuaObject* obj2);
//  LuaObject getTableElement(const LuaTableElement& el);
  void setTableElement(const LuaObject*, const LuaTableElement& el);
  void setTableElementValue(const LuaTable*, const LuaObject*, const LuaObject*);
  
  
  bool isNumber(const LuaObject*);
  bool isString(const LuaObject*);
  bool isFunction(const LuaObject*);
  bool isTable(const LuaObject*);
  std::string typeName(const LuaObject*);
  
  LuaTable* globalTable; 
  
  static int generalFunction(lua_State* state);
  
  template <typename T>
  static int generalTemplateFunction(lua_State* state) {
    T* obj = reinterpret_cast<T*>(lua_touserdata(state, lua_upvalueindex(1)));
    void* ptmf = lua_touserdata(state, lua_upvalueindex(2));
    int (T::*f)(LuaState*);
    std::memcpy(&f, ptmf, sizeof(int (T::*)(LuaState*)));
    LuaState tempState(state);
    return (obj->*f)(&tempState);
  }
public:
  LuaState();
  LuaState(lua_State*);
  ~LuaState();
  
  // basic libraries
  void openBase();
  void openIO();
  void openTable();
  void openString();
  void openMath();
  
  LuaTableElement operator[](const LuaObject&);
  inline int top() const { return lua_gettop(L); }
  LuaFunction loadFile(const char*);
  void doFile(const char*);
  
  LuaFunction createFunction(cppluaFunction* f);
  template <typename T> LuaFunction createFunction(T& object, int(T::*f)(LuaState*)) {
    LuaFunction res = createFunctionFromObject();
    lua_pushlightuserdata(L, &res);
    lua_pushlightuserdata(L, reinterpret_cast<void*>(&object));
    void* ptmf = lua_newuserdata(L, sizeof(int(T::*)(LuaState*)));
    std::memcpy(ptmf, &f, sizeof(int(T::*)(LuaState*)));
    lua_pushcclosure(L, LuaState::generalTemplateFunction<T>, 2);
    lua_settable(L, cppluaTableIndex);
    return res;
  }
  
  LuaFunction createFunctionFromObject();
    
  void reg(cppluaFunction* f, const char* name) {
    lua_pushcfunction(L, reinterpret_cast<cluaFunction*>(f));
    lua_pushcclosure(L, LuaState::generalFunction, 1);
    lua_setglobal(L, name);
  }
  
  // casting f to void* or cluaFunction does not work!
  // a pointer-to-member-function is not guaranteed to have the same size as
  // a pointer-to-object or a pointer-to-function, so it cannot be pushed in the lua
  // stack as a light userdatum. A possible solution is to use full userdata.
  
  template <typename T> void reg(T& object, int(T::*f)(LuaState*), const char* name) {
    lua_pushlightuserdata(L, reinterpret_cast<void*>(&object));
    void* ptmf = lua_newuserdata(L, sizeof(int(T::*)(LuaState*)));
    std::memcpy(ptmf, &f, sizeof(int(T::*)(LuaState*)));
    lua_pushcclosure(L, generalTemplateFunction<T>, 2);
    lua_setglobal(L, name);
  }
  
  LuaObject getNil() const;
};

}

#endif
