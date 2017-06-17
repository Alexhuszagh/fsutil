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
// MACROS
// ------

/**
 *  Make error code from descriptor.
 */
#define MAKE_ERROR(name) std::make_error_code(std::errc::name)

// DETAIL
// ------

#if defined(_WIN32)                 // WINDOWS


static void handle_error(const path_t& path, int code)
{
    switch (code) {
        case 0:
            return;
        case ENOENT:
            throw fs::filesystem_error("File not found.", path, MAKE_ERROR(no_such_file_or_directory));
         case EINVAL:
            throw fs::filesystem_error("Invalid parameter to _stat.", path, MAKE_ERROR(invalid_argument));
         default:
            throw fs::filesystem_error("Unexpected error in stat.", path, MAKE_ERROR(not_supported));
    }
}


static void copy_native(const struct _stat& src, stat_t& dst)
{
    dst.st_dev = src.st_dev;
    dst.st_ino = src.st_ino;
    dst.st_mode = src.st_mode;
    dst.st_nlink = src.st_nlink;
    dst.st_uid = src.st_uid;
    dst.st_gid = src.st_gid;
    dst.st_rdev = src.st_rdev;
    dst.st_size = src.st_size;
//    dst.st_atime = src.st_atime;
//    dst.st_mtime = src.st_mtime;
//    dst.st_ctime = src.st_ctime;
}


stat_t stat_windows(const path_t& path)
{
    struct _stat sb;
    stat_t data;
    int code;

    code = ::_stat(path.wstring().data(), &sb);
    handle_error(path, code);
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
            throw fs::filesystem_error("File not found.", path, MAKE_ERROR(no_such_file_or_directory));
        case EINVAL:
            throw fs::filesystem_error("Invalid parameter to stat.", path, MAKE_ERROR(invalid_argument));
        case ENOMEM:
            throw fs::filesystem_error("Out of memory.", path, MAKE_ERROR(not_enough_memory));
        default:
            throw fs::filesystem_error("Unexpected error in stat.", path, MAKE_ERROR(not_supported));
    }
}


static void copy_native(const struct stat& src, stat_t& dst)
{
    dst.st_dev = src.st_dev;
    dst.st_ino = src.st_ino;
    dst.st_mode = src.st_mode;
    dst.st_nlink = src.st_nlink;
    dst.st_uid = src.st_uid;
    dst.st_gid = src.st_gid;
    dst.st_rdev = src.st_rdev;
    dst.st_size = src.st_size;
// TODO: these are macros for st_atim, etc.
// Need to make sure they're compatible... Fuck
//    dst.st_atime = src.st_atime;
//    dst.st_mtime = src.st_mtime;
//    dst.st_ctime = src.st_ctime;
}


stat_t stat_posix(const path_t& path)
{
    struct stat sb;
    stat_t data;
    int code;

    code = ::stat(path.c_str(), &sb);
    handle_error(path, code);
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
