//  :copyright: (c) 2017 Alex Huszagh.
//  :license: MIT, see LICENSE.md for more details.

#if !defined(_WIN32)                // POSIX

#include "config.h"

// TESTS
// -----


TEST(normalization, normpath)
{
    EXPECT_PATH_EQ(fsutil::normpath("."), ".");
    EXPECT_PATH_EQ(fsutil::normpath("./"), ".");
    EXPECT_PATH_EQ(fsutil::normpath("./.."), "..");
    EXPECT_PATH_EQ(fsutil::normpath(".."), "..");
    EXPECT_PATH_EQ(fsutil::normpath("../"), "..");
    EXPECT_PATH_EQ(fsutil::normpath("/."), "/");
    EXPECT_PATH_EQ(fsutil::normpath("/.."), "/");
    EXPECT_PATH_EQ(fsutil::normpath("/usr/bin"), "/usr/bin");
    EXPECT_PATH_EQ(fsutil::normpath("/usr/bin/fakeroot"), "/usr/bin/fakeroot");
    EXPECT_PATH_EQ(fsutil::normpath("/usr/bin/./.."), "/usr");
    EXPECT_PATH_EQ(fsutil::normpath("./include"), "include");
    EXPECT_PATH_EQ(fsutil::normpath("./../bin/include"), "../bin/include");
}


TEST(normalization, realpath)
{
//    fsutil::path_t symlink("../test/file/link");
//    auto file = fsutil::realpath(symlink);
//    EXPECT_FALSE(symlink == file);
}

#endif
