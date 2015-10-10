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
#ifndef LUAFUNCTION_H
#define LUAFUNCTION_H

#include <vector>
#include "luaobject.h"

namespace cpplua {

typedef std::vector<LuaObject> ReturnValueList;
typedef std::vector<const LuaObject*> ArgumentList;

class LuaFunction : public LuaObject {
private:
  ArgumentList argumentList;
  ReturnValueList returnValues;
  int nReturnValues;
  
public:
  explicit LuaFunction(int nReturn = 1, LuaState* l = 0) : LuaObject(l), nReturnValues(nReturn) {}
  LuaFunction(const LuaObject& obj, int nReturn = 1) : LuaObject(obj) { nReturnValues = nReturn; }
  LuaFunction(const LuaTableElement& te, int nReturn = 1, LuaState* state = 0) : LuaObject(te, state) {
    nReturnValues = nReturn;
  }
  
  void clearArgumentList() { argumentList.clear(); }
  void addArgument(const LuaObject* obj) { argumentList.push_back(obj); }
  int returnValueCount() const { return returnValues.size(); }
  const LuaObject& getReturnValue(int i) { return returnValues[i]; }
  void call();
  
  ReturnValueList& operator()();
  ReturnValueList& operator()(const ArgumentList& aList);
  ReturnValueList& operator()(const LuaObject&);
};

};

#endif

