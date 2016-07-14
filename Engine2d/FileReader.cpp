#include "FileReader.h"
#include <iostream>
#include <fstream>

namespace Engine2d
{
	bool FileReader::readTextFile(const std::string & path, std::string & buffer)
	{
		std::ifstream fileStream(path);
		std::string lineBuffer;

		if (!fileStream.is_open()) {
			std::cout << "file error" << std::endl;
			std::quick_exit(1);
			return false;
		}

		while (fileStream.good()) {
			std::getline(fileStream, lineBuffer);
			buffer.append(lineBuffer + "\n");
		}

		fileStream.close();

		return true;
	}
}