#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <vector>

namespace Grim
{
	class File
	{
	public:
		static bool isFileEmpty(std::fstream& file);
		static bool doesFileExist(const std::string& file);
	};
}

#endif