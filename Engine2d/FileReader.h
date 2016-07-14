#pragma once
#include <string>
#include <fstream>

namespace Engine2d 
{
	class FileReader
	{
	public:
		static bool readTextFile(const std::string & path, std::string & buffer);
	};
}