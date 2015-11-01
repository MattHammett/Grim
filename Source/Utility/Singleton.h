#ifndef SINGLETON_H
#define SINGLETON_H

#include "NonCopy.h"

#define GRIM_SINGLETON friend class Singletons;

namespace Grim
{
	template<typename T>
	class Singleton : public NonCopy
	{
	public:
		static T& instance()
		{
			static T m_Instance;
			return m_Instance;
		}
	protected:
		explicit Singleton<T>() {};

		virtual void initialize() = 0;
		virtual void terminate() = 0;
	};
}

#endif