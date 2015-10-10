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
#ifndef LUATABLE_H
#define LUATABLE_H

#include "luaobject.h"
#include <iostream>

namespace cpplua {

class LuaTable : public LuaObject {
private:
  friend class LuaTableElement;
  void setElement(const LuaObject* key, const LuaObject& value);
  LuaObject next(const LuaObject& key) const;
public:

  class iterator;
  
  LuaTable(const LuaObject& obj) : LuaObject(obj) {}
  LuaTable(const LuaTableElement& te, LuaState* state = 0): LuaObject(te, state) {}

  iterator begin() const;
  iterator end() const;
  
  LuaTableElement operator[](const LuaObject& key);
};


class LuaTableElement {
private:
  LuaTable table;
  const LuaObject* key;
public:
  explicit LuaTableElement(const LuaTable& table, const LuaObject& key) :
    table(table), key(&key) {}
  LuaTableElement(const LuaTableElement& el) : table(el.table), key(el.key) {}
  LuaTableElement(const LuaTable& table) : table(table), key(0) {}
  const LuaTable& getTable() const { return table; }
  const LuaObject& getKey() const { return *key; }
  void setKey(const LuaObject* newKey) { key = newKey; }
  
  LuaTableElement& operator=(const LuaObject& obj);
  bool operator==(const LuaObject& obj) const;
  inline bool operator==(const LuaTableElement& el) const {
    return key!=0 && key==el.key && table==el.table;
  }
  bool operator!=(const LuaObject& obj) const;

};

class LuaTable::iterator {
  friend class LuaTable;
private:
  LuaTableElement el;
  iterator(const LuaTable& table, const LuaObject& key) : el(table, key) {}
  iterator(const LuaTable& table) : el(table) {}
public:
  iterator(const iterator& it) : el(it.el) {}
  iterator& operator++();
  iterator operator++(int);
  LuaTableElement operator*() const;
  const LuaTableElement* operator->() const;
  inline bool operator==(const iterator& other) const {
    return el==other.el;
  }
  inline bool operator!=(const iterator& other) const {
    return !(el==other.el);
  }
};

};

#endif
