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
#include "../../../Include/Lua/cpplua-0.2/luaobject.h"
#include "../../../Include/Lua/cpplua-0.2/luastate.h"
#include "../../../Include/Lua/cpplua-0.2/luafunction.h"
#include "../../../Include/Lua/cpplua-0.2/luatable.h"

using namespace std;

namespace cpplua {

LuaObject::LuaObject(LuaState* state) {
  setState(state);
  check_consistency();
}

LuaObject::LuaObject(const LuaObject& other) {
  l = other.l;
  l->duplicateEntry(this, &other);
  check_consistency(); 
}

LuaObject::LuaObject(const char* s, LuaState* state) {
  setState(state);
  l->setString(this, s);
  check_consistency();
}

LuaObject::LuaObject(int n, LuaState* state) {
  setState(state);
  l->setNumber(this, n);
  check_consistency(); 
}

LuaObject::LuaObject(const LuaTableElement& el, LuaState* state) {
  setState(state);
  l->setTableElement(this, el);
  check_consistency(); 
}

LuaObject::~LuaObject() {
  check_consistency(); 
  l->removeEntry(this);
}

// conversions

int LuaObject::toNumber() {
  if (!l->isNumber(this))
    throw InvalidConversion();
  return l->getNumber(this);
}

string LuaObject::toString() const {
  if (!l->isString(this))
    throw InvalidConversion();
  return l->getString(this);
}

LuaFunction LuaObject::toFunction(int nReturn) {
  if (!l->isFunction(this))
    throw InvalidConversion();
  return LuaFunction(*this, nReturn);
}

LuaTable LuaObject::toTable() const {
  if (!l->isTable(this))
    throw InvalidConversion();
  return LuaTable(*this);
}

// comparison

bool LuaObject::operator==(const LuaObject& other) const {
  return l->equal(this, &other);
}

bool LuaObject::operator!=(const LuaObject& other) const {
  return !(l->equal(this, &other));
}

};
