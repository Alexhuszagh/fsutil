//  :copyright: (c) 2017 Alex Huszagh.
//  :license: MIT, see LICENSE.md for more details.

#if !defined(_WIN32)                // POSIX

#include <fsutil.h>
#include <gtest/gtest.h>

// TESTS
// -----


TEST(normalization, normpath)
{
    EXPECT_TRUE(fsutil::normpath(".") == ".");
    EXPECT_TRUE(fsutil::normpath("./") == ".");
    EXPECT_TRUE(fsutil::normpath("./..") == "..");
    EXPECT_TRUE(fsutil::normpath("..") == "..");
    EXPECT_TRUE(fsutil::normpath("../") == "..");
    EXPECT_TRUE(fsutil::normpath("/.") == "/");
    EXPECT_TRUE(fsutil::normpath("/..") == "/");
    EXPECT_TRUE(fsutil::normpath("/usr/bin") == "/usr/bin");
    EXPECT_TRUE(fsutil::normpath("/usr/bin/fakeroot") == "/usr/bin/fakeroot");
    EXPECT_TRUE(fsutil::normpath("/usr/bin/./..") == "/usr");
    EXPECT_TRUE(fsutil::normpath("./include") == "include");
    EXPECT_TRUE(fsutil::normpath("./../bin/include") == "../bin/include");
}


#if defined(__linux__)           // LINUX

TEST(normalization, realpath)
{
    fsutil::path_t libc_link("/lib/libc.so.6");
    auto libc = fsutil::realpath(libc_link);
    EXPECT_FALSE(libc_link == libc);
}

#endif


#endif