//  :copyright: (c) 2017 Alex Huszagh.
//  :license: MIT, see licenses/mit.md for more details.
/**
 *  \addtogroup fsutil
 *  \brief File system manipulation routines.
 */

#include <fsutil.h>


namespace fsutil
{
// API
// ---


void copyfileobj(istream_t& fsrc, ostream_t& fdst, size_t length)
{
    // read entire file in single shot
    if (length == SIZE_MAX) {
        fdst << fsrc.rdbuf();
        return;
    }

    // read chunks of file to minimize memory usage
    // TODO: here...
}

}   /* fsutil */
