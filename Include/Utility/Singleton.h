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

		bool checkForError() const { return m_Errored; };
	protected:
		explicit Singleton<T>() {};

		virtual void initialize() = 0;
		virtual void terminate() = 0;

		bool m_Errored = false;
	};
}

#endif