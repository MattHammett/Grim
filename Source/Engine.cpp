#include "../Include/Engine.h"
#include "../Include/Singletons.h"
#include "../Include/Setup.h"
#include <iostream>
using namespace Grim;

int32 Engine::run()
{
	Singletons::initialize();

	m_Running = true;

	while (m_Running)
	{
		std::cout << "Hello World!" << std::endl;
	}

	Singletons::terminate();
	return GRIM_EXIT_SUCCESS;
}

void Engine::exit()
{
	m_Running = false;
}
