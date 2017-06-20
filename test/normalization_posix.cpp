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


TEST(normalization, realpath)
{
    fsutil::path_t symlink("../test/file/link");
    auto file = fsutil::realpath(symlink);
    EXPECT_FALSE(symlink == file);
}

#endif
