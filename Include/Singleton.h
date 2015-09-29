#ifndef SINGLETON_H
#define SINGLETON_H

#include "NonCopy.h"

namespace Grim
{
	template<typename T>
	class Singleton : private NonCopy
	{
	public:
		static T& instance()
		{
			static T m_Instance;
			return m_Instance;
		}

		virtual void initialize() = 0;
		virtual void terminate() = 0;
	protected:
		explicit Singleton<T>() {};
	};
}

#endif