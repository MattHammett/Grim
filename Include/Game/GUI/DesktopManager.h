#ifndef DESKTOP_MANAGER_H
#define DESKTOP_MANAGER_H

#include "../../Utility/Singleton.h"

namespace Grim
{
	class DesktopManager : public Singleton<DesktopManager>
	{
		GRIM_SINGLETON
	public:
		void initialize() override;
		void terminate() override;
	private:

	};
}

#endif