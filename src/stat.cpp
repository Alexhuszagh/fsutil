//  :copyright: (c) 2017 Alex Huszagh.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup fsutil
 *  \brief Cross-platform stat utilities.
 */

#include <fsutil.h>

#include <errno.h>
#include <sys/stat.h>


namespace fsutil
{
// DETAIL
// ------

#if defined(_WIN32)                 // WINDOWS


static void handle_error(const path_t& path, int code)
{
    switch (code) {
        case 0:
            return;
        case ENOENT:
            throw fs::filesystem_error("File not found.", path, std::erc::no_such_file_or_directory);
         case EINVAL:
//            throw fs::filesystem_error("Invalid parameter to _stat.", path, code);
         default:
            throw fs::filesystem_error("Unexpected error in _stat.", path);
    }
}


static void copy_native(const _stat& src, stat_t& dst)
{
    // TODO: here....
}


stat_t stat_windows(const path_t& path)
{
    struct _stat sb;
    stat_t data;
    handle_error(::_stat(path.wstring().data(), &sb));
    copy_native(sb, data);

    return data;
}

#else                               // POSIX

static void handle_error(const path_t& path, int code)
{
    switch (code) {
        case 0:
            return;
        case ENOENT:
            throw fs::filesystem_error("File not found.", path, std::erc::no_such_file_or_directory);
        case EINVAL:
//            throw fs::filesystem_error("Invalid parameter to stat.", path, code);
        case ENOMEM:
//            throw fs::filesystem_error("Out of memory.", path, code);
        default:
            throw fs::filesystem_error("Unexpected error in stat.", path);
    }
}


static void copy_native(const stat& src, stat_t& dst)
{
    // TODO: here....
}


stat_t stat_posix(const path_t& path)
{
    struct stat sb;
    stat_t data;
    handle_error(::stat(path.c_str(), &sb));
    copy_native(sb, data);

    return data;
}

#endif

// API
// ---


stat_t stat(const path_t& path)
{
#if defined(_WIN32)                 // WINDOWS
    return stat_windows(path);
#else                               // POSIX
    return stat_posix(path);
#endif
}

}   /* fsutil */
