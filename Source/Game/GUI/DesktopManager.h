#ifndef DESKTOP_MANAGER_H
#define DESKTOP_MANAGER_H

#include "../../Utility/Singleton.h"
#include "../../Utility/Interfaces/Handle.h"
#include "../../Utility/Interfaces/Tick.h"
#include "../../Utility/Interfaces/Render.h"
#include "Desktop.h"

namespace Grim
{
	class DesktopManager : public Singleton<DesktopManager>, public Handle, public Tick, public Render
	{
		GRIM_SINGLETON
	public:
		void initialize() override;
		void terminate() override;

		void handle(sf::RenderWindow& target, sf::Event& events) override;
		void tick(sf::RenderWindow& target, float32 dt) override;
		void render(sf::RenderTarget& target, sf::RenderStates& state) override;

		void add(Desktop::Pointer desktop);
	private:
		Desktop::Vector m_Desktops;
	};
}

#endif