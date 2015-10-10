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
#ifndef COMMON_H
#define COMMON_H

#include <stdexcept>

namespace cpplua {

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

class cppluaError : public std::logic_error {
public:
  cppluaError() : std::logic_error("") {}
};

class LuaRuntimeError : public std::runtime_error {
public:
  LuaRuntimeError(const char* msg) : std::runtime_error(msg) {}
};

class cppluaIteratorOutOfRange : public std::runtime_error {
public:
  cppluaIteratorOutOfRange() : std::runtime_error("") {}
};

};

#endif
