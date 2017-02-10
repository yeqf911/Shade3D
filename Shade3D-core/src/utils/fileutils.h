#ifndef _FILEUTILS_H_
#define _FILEUTILS_H_
#include <string>

namespace Shade
{
	inline std::string read_file(const char* filepath)
	{
		FILE* fp = fopen(filepath, "rt");
		if (fp == nullptr)
		{
			// TODO: error print
			return std::string();
		}

		fseek(fp, 0, SEEK_END);
		unsigned long length = ftell(fp);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(fp, 0, SEEK_SET);
		fread(data, 1, length, fp);
		fclose(fp);
		std::string str(data);
		delete[] data;
		return str;
	}
}

#endif // _FILEUTILS_H_
