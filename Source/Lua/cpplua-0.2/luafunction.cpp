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
#include "../../../Include/Lua/cpplua-0.2/luafunction.h"
#include "../../../Include/Lua/cpplua-0.2/luastate.h"
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

namespace cpplua {

void LuaFunction::call() {
  int argc = argumentList.size();
  for(int i=0; i<argc; i++)
    getState()->pushEntry(argumentList[i]);
  getState()->call(this, argc, nReturnValues);
  returnValues.clear();
  // todo
  /*  returnValues.resize(nReturnValues);
      for(int i=0; i<nReturnValues; i++)
      returnValues.push_back(getState()->popEntry());*/
}

ReturnValueList& LuaFunction::operator()() {
  clearArgumentList();
  call();
  return returnValues;
}

ReturnValueList& LuaFunction::operator()(const ArgumentList& aList) { 
  clearArgumentList();
  copy(aList.begin(), aList.end(), back_inserter(argumentList));
  call(); 
  return returnValues;
}

ReturnValueList& LuaFunction::operator()(const LuaObject& obj) {
  clearArgumentList();
  argumentList.push_back(&obj);
  call();
  return returnValues;
}


};
