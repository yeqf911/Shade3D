#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <iostream>

namespace Shade
{
	template<typename T>
	inline void LOG(const char* TAG, const T logInfo)
	{
		std::cout << TAG << logInfo << std::endl;
	}
}

#endif // _LOGGER_H_
