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
#include "../../../Include/Lua/cpplua-0.2/luatable.h"
#include "../../../Include/Lua/cpplua-0.2/luastate.h"
#include "../../../Include/Lua/cpplua-0.2/common.h"

namespace cpplua {

LuaTableElement& LuaTableElement::operator=(const LuaObject& obj) {
  table.setElement(key, obj);
  return *this;
}

bool LuaTableElement::operator==(const LuaObject& obj) const {
  return LuaObject(*this)==obj;
}

bool LuaTableElement::operator!=(const LuaObject& obj) const {
  return LuaObject(*this)!=obj;
}


void LuaTable::setElement(const LuaObject* key, const LuaObject& value) {
  getState()->setTableElementValue(this, key, &value);
}

LuaTableElement LuaTable::operator[](const LuaObject& key) {
  return LuaTableElement(*this, key);
}

LuaTable::iterator LuaTable::begin() const {
  return iterator(*this, getState()->getNil());
}

LuaTable::iterator LuaTable::end() const {
  return iterator(*this); 
}

LuaObject LuaTable::next(const LuaObject& key) const {
  int res = getState()->next(this, &key);
  if(res != 0)
    return getState()->popEntry(1);
  else
    return getState()->getNil();
}

LuaTable::iterator& LuaTable::iterator::operator++() {
  if (el.getKey() == 0)
    throw cppluaIteratorOutOfRange();
  LuaObject nextKey = el.getTable().next(el.getKey());
  if (nextKey == el.getTable().getState()->getNil()) 
    el.setKey(0);
  else
    el.setKey(&nextKey);
  return *this;
}

LuaTableElement LuaTable::iterator::operator*() const {
  return el;
}

};
