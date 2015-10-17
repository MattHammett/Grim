#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <vector>

namespace Grim
{
	class File
	{
	public:
		static bool checkFileEmpty(std::fstream& file);
		static bool checkFileExists(const std::string& file);
	};
}

#endif