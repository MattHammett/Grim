#ifndef ENGINE_H
#define ENGINE_H

#include "Type.h"

namespace Grim
{
	class Engine
	{
	public:
		int32 run();
		void exit();
	private:
		void initialize();
	private:
		bool m_Running;
	};
}

#endif