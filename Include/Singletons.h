#ifndef SINGLETONS_H
#define SINGLETONS_H

#include "Log.h"

namespace Grim
{
	class Singletons
	{
	public:
		static void initialize();
		static void terminate();

		static Log& log;
	private:
		explicit Singletons();
	};
}

#endif