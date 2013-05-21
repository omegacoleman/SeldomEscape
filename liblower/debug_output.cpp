
#include "global.hpp"
#include "debug_output.hpp"

#ifdef _MSC_VER
#   include <sstream>
std::ostringstream debug_dump(std::ostringstream::ate);
#endif

/**
 * Clear the debug buffer and output the debug message.
 */
void debug_flush(void)
{
    #ifdef _MSC_VER
    MessageBox(NULL, debug_dump.str().c_str(), "SE Debug", MB_OK);
    debug_dump.str("");
    debug_dump.clear();
    debug_dump << "======" << std::endl;
    #endif
}

