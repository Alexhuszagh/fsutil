//  :copyright: (c) 2017 Alex Huszagh.
//  :license: MIT, see licenses/mit.md for more details.
/**
 *  \addtogroup fsutil
 *  \brief Path normalization routines.
 */

#include <fsutil.h>


namespace fsutil
{
// API
// ---


path_t abspath(const path_t& path)
{
    return fs::absolute(path);
}


path_t basename(const path_t& path)
{
    return path.filename();
}


path_t dirname(const path_t& path)
{
    return path.parent_path();
}


bool exists(const path_t& path)
{
    return fs::exists(path);
}

}   /* fsutil */
