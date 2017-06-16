//  :copyright: (c) 2017 Alex Huszagh.
//  :license: MIT, see licenses/mit.md for more details.
/**
 *  \addtogroup fsutil
 *  \brief fsutil public header.
 *
 *  This module defines the public API for fsutil.
 */

#pragma once

#include "stat.h"

#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;


namespace fsutil
{
// ALIAS
// -----

typedef fs::path path_t;
typedef double date_t;
typedef std::istream istream_t;
typedef std::ostream ostream_t;

// CONSTANTS
// ---------

constexpr size_t BUFSIZE = 16 * 1024;

// API
// ---

// STAT

/** \brief POSIX-like stat call.
 */
stat_t stat(const path_t& path);

// NORMALIZATION

/** \brief Return the absolute path relative to the base.
 */
path_t abspath(const path_t& path);

/** \brief Return name of file, relative to parent directory.
 */
path_t basename(const path_t& path);

/** \brief Return the path of the parent directory.
 */
path_t dirname(const path_t& path);

/** \brief Check if path exists on filesystem.
 */
bool exists(const path_t& path);

// TODO: need to have tge home and temp directories
// Need to access them reliably, in a cross-platform manner
//path_t expanduser(const path_t& path);
//path_t expandvars(const path_t& path);


//double getatime(const path_t& path);
//double getmtime(const path_t& path);
//double getctime(const path_t& path);
//size_t getsize(const path_t& path);
//bool isfile(const path_t& path);
//bool isdir(const path_t& path);
//bool islink(const path_t& path);
//bool ismount(const path_t& path);

//path_t normcase(const path_t& path);
//path_t normpath(const path_t& path);
//path_t realpath(const path_t& path);
//path_t relpath(const path_t& path);
//path_t relpath(const path_t& path, const path_t& start);
// samefile
// samestat
// sameopenfile
// split
// splitdrive
// splitunc
// TODO:

// MANIPULATIONS

///** \brief Copy contents of fsrc to fdst, reading the file in chunks.
// */
//void copyfileobj(istream_t& fsrc, ostream_t& fdst, size_t length = BUFSIZE);
//
///** \brief Copy a file from src to the file dst.
// */
//void copyfile(const path_t& src, const path_t& dst);
//
///** \brief Copy permissions from src to dst.
// */
//void copymode(const path_t& src, const path_t& dst);
//
///** \brief Copy permissions, access and modification times from src to dst.
// */
//void copystat(const path_t& src, const path_t& dst);
//
///** \brief Copy src file to dst.
// */
//void copy(const path_t& src, const path_t& dst);
//
///** \brief Copy data and metadata.
// */
//void copy2(const path_t& src, const path_t& dst);

//void copytree(const path_t& src, const path_t& dst, symlinks, ignore);
//void move(const path_t& src, const path_t& dst);
//void mkdir(const path_t& dir, uint32_t mode);
//void makedirs(const path_t& dir, uint32_t mode);
//void remove(const path_t& path);
//void rename(const path_t& src, const path_t& dst);
//void rmdir(const path_t& path);
//void rmtree(const path_t& path);

// TODO: need temporary file support....

// TODO: need stat support....

}   /* fsutil */
