#ifndef ENGINE_H
#define ENGINE_H

#include "Utility\Type.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "Game/GUI/DesktopManager.h"
#include "Game\GUI\Desktop.h"
#include "Game\GUI\Container.h"
#include "Game\GUI\Component.h"
#include "Game\GUI\Label.h"

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

		void render(float32 stateRender);
	private:
		sf::RenderWindow m_RenderWindow;
		bool m_bRunning;
		int32 m_ExitCode;

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