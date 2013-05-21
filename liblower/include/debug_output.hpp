
#ifndef _DEBUG_OUTPUT_HPP_
#define _DEBUG_OUTPUT_HPP_

#include <iostream>

#ifdef _MSC_VER
    #include <sstream>
    extern std::ostringstream debug_dump;
#endif

/**
 * Log a piece of debug message.
 */
template <class T> void debug_log(const T& s)
{
    #ifdef _MSC_VER
    debug_dump << s;
    debug_dump << std::endl;
    #else
    std::cerr << s << std::endl;
    #endif
};

/**
 * Clear the debug buffer and output the debug message.
 */
void debug_flush(void);

#endif

