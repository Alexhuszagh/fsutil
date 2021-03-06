//  :copyright: (c) 2017 Alex Huszagh.
//  :license: MIT, see licenses/mit.md for more details.
/**
 *  \addtogroup fsutil
 *  \brief Path normalization routines.
 */

#include <fsutil.h>

#include <deque>


namespace fsutil
{
// CONSTANTS
// ---------

#if defined(_WIN32)                // WINDOWS

static const std::wstring CURRENT_DIR(L".");
static const std::wstring PARENT_DIR(L"..");

#else

static const std::string CURRENT_DIR(".");
static const std::string PARENT_DIR("..");

#endif

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


time_t getatime(const path_t& path)
{
    return stat(path).st_atim.tv_sec;
}


time_t getmtime(const path_t& path)
{
    return stat(path).st_mtim.tv_sec;
}


time_t getctime(const path_t& path)
{
    return stat(path).st_ctim.tv_sec;
}


off_t getsize(const path_t& path)
{
    return stat(path).st_size;
}


bool isfile(const path_t& path)
{
    return fs::is_regular_file(path);
}


bool isdir(const path_t& path)
{
    return fs::is_directory(path);
}


bool islink(const path_t& path)
{
    return fs::is_symlink(path);
}

// TODO: implement....
// bool ismount(const path_t& path);

// TODO: normcase needs to call make_preferred


path_t normpath(const path_t& path)
{
    // begin our path
    path_t preferred;
    auto it = path.begin();

    // check root name and directory, and add those manually
    if (path.has_root_name()) {
        preferred += path.root_name();
        ++it;
    }
    if (path.has_root_directory()) {
        preferred += path_t::preferred_separator;
        ++it;
    }

    // get our directory separators
    std::deque<typename path_t::string_type> buffer;
    for (; it != path.end(); ++it) {
        auto &p = *it;
        if (p == CURRENT_DIR) {
            // skip unless there is no root path or current path
            if (preferred.empty() && buffer.empty() && std::distance(it, path.end()) == 1) {
                buffer.push_back(p);
            }
        } else if (p == PARENT_DIR) {
            // Erase if the buffer is not empty and the last element is not ..
            // otherwise, we have a relative path, and need to keep the item
            // If the path is "./..", we just want "..".
            // If the buffer is empty and it has a root path, we're already
            // at the root, so skip the item. Otherwise, we have a relative
            // path, so add the element.
            if (!buffer.empty()) {
                auto &parent = buffer.back();
                if (parent == CURRENT_DIR) {
                    buffer.erase(buffer.end()-1);
                    buffer.push_back(p);
                } else if (parent == PARENT_DIR) {
                    buffer.push_back(p);
                } else {
                    buffer.erase(buffer.end()-1);
                }
            } else if (preferred.empty()) {
                buffer.push_back(p);
            }
        } else {
            buffer.push_back(p);
        }
    }

    // add the normalize elements to the path
    for (auto p: buffer) {
        preferred /= p;
    }

    return preferred;
}


path_t realpath(const path_t& path)
{
    auto path_ = path;
    if (path_.has_parent_path()) {
        path_ = realpath(path_.parent_path()) / path_.filename();
    }

    auto status = fs::symlink_status(path_);
    if (fs::exists(status) && fs::is_symlink(status)) {
        auto read = fs::read_symlink(path_);
        if (read.is_absolute()) {
            return read;
        } else {
            return path_.parent_path() / read;
        }
    }

    return path_;
}


// abspath = normpath(join(os.getcwd(), path))
// TODO:....

}   /* fsutil */
