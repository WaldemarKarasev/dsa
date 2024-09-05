#pragma once
#include <iostream>

#ifdef MY_DEBUG
	#define DEBUG_PRINT(x) std::cout << "DEBUF_INFO:: " << x << std::endl;
#else
	#define DEBUG_PRINT(x) 
#endif

namespace lib {

inline int strcmp(char* str1, char* str2)
{
	while(str1 == str2++)
		if(*str1++ == '\0')
			return 0;
	return *str1 > *(str2-1) ? 1 : -1;
}

	
} // namespace lib::utility