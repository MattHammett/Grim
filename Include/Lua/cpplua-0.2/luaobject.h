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
#ifndef LUA_OBJECT_H
#define LUA_OBJECT_H

#include "common.h"
#include "luastate.h"
#include <iostream>
#include <cassert>

namespace cpplua {

class LuaState;
class LuaFunction;
class LuaTableElement;
class LuaTable;
class InvalidConversion : public cppluaError {};

//#define _DEBUG
 
class LuaObject {
private:
  LuaState* l;
  
  inline void setState(LuaState* state) {
    if (state)
      l = state;
    else
      l = LuaState::getCurrentState();
  }

  inline void LuaObject::check_consistency() const {
#ifdef _DEBUG
    assert(l != 0);
    std::cout << "assertion passed" << std::endl;
#endif
  }
  
protected:
  inline LuaState* getState() const { return l; }
public:
  explicit LuaObject(LuaState* l = 0);
  LuaObject(const LuaObject& other);
  LuaObject(const char* s, LuaState* state = 0);
  LuaObject(int n, LuaState* state = 0);
  
  LuaObject(const LuaTableElement& el, LuaState* state = 0);
  virtual ~LuaObject();
  
  inline bool isString() const { return l->isString(this); }
  inline bool isNumber() const { return l->isNumber(this); }
  inline bool isFunction() const { return l->isFunction(this); }
  inline bool isTable() const { return l->isTable(this); }
  inline LuaState::LuaType getType() const { return l->getType(this); }
  
  bool operator==(const LuaObject& other) const;
  bool operator!=(const LuaObject& other) const;
  
  std::string toString() const;
  int toNumber();
  LuaFunction toFunction(int nReturn = 1);
  LuaTable toTable() const;
  
  std::string typeName() const { return l->typeName(this); }
};

}; // end namespace cpplua

#endif
