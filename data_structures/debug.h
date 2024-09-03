s#ifndef MYDEBUG_H
#define MYDEBUG_H

#include <iostream>

#ifdef MY_DEBUG
	#define DEBUG_PRINT(x) std::cout << "DEBUF_INFO:: " << x << std::endl;
#else
	#define DEBUG_PRINT(x) 
#endif


#endif // MYDEBUG_H