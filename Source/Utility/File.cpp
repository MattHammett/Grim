#include "File.h"
#include <filesystem>
using namespace Grim;

bool File::isFileEmpty(std::fstream& file)
{
	file.seekg(0, std::ios::end);
	int length = static_cast<int>(file.tellg());
	return (length == 0) ? true : false;
}

bool File::doesFileExist(const std::string& file)
{
	return std::experimental::filesystem::exists(file);
}