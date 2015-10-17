#ifndef ENGINE_H
#define ENGINE_H

#include "Utility\Type.h"
#include "../Include/Game/Entity/Player/Player.h"
#include <SFML\Graphics\RenderWindow.hpp>

namespace Grim
{
	class Engine
	{
	public:
		explicit Engine();
		~Engine();
		void run();
		void exit();

		void setExitCode(int32 exitCode);
		int32 getExitCode() const;
	private:
		bool tryInitializeSingletons();
		bool tryInitializeWindow();
		bool tryRunGameLoop();

		void integrate(float32 stateCurrent, float32 dt);
		void render(float32 stateRender);
	private:
		sf::RenderWindow m_RenderWindow;
		bool m_Running;
		int32 m_ExitCode;

		//Testing
		Player* m_Player;

		// Fixed time step
		float32 m_t;
		float32 m_dt;
		float32 m_CurrentTime;
		float32 m_Accumulator;
		float32 m_StatePrevious;
		float32 m_StateCurrent;
		float32 m_NewTime;
		float32 m_FrameTime;
		float32 m_FrameAlpha;
	};
}

#endif