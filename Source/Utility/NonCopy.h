#ifndef NON_COPY_H
#define NON_COPY_H

namespace Grim
{
	class NonCopy
	{
	protected:
		NonCopy() {};
		~NonCopy() {};
	private:
		explicit NonCopy(const NonCopy& other);
		const NonCopy& operator=(const NonCopy& other);
	};
}

#endif