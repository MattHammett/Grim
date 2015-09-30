#ifndef ENGINE_H
#define ENGINE_H

#include "Utility\Type.h"
#include <SFML\Graphics\RenderWindow.hpp>

namespace Grim
{
	class Engine
	{
	public:
		explicit Engine();
		~Engine();
		int32 run();
		void exit();

	private:
		bool m_Running;
		sf::RenderWindow m_RenderWindow;
	};
}

#endif