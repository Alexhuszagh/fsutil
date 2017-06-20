//  :copyright: (c) 2017 Alex Huszagh.
//  :license: MIT, see LICENSE.md for more details.

#if defined(_WIN32)                // WINDOWS

#include <fsutil.h>
#include <gtest/gtest.h>

// TESTS
// -----


TEST(normalization, normpath)
{
    EXPECT_TRUE(fsutil::normpath(".") == ".");
    EXPECT_TRUE(fsutil::normpath("./") == ".");
    EXPECT_TRUE(fsutil::normpath(".\\") == ".");
    EXPECT_TRUE(fsutil::normpath("./..") == "..");
    EXPECT_TRUE(fsutil::normpath(".\\..") == "..");
    EXPECT_TRUE(fsutil::normpath("..") == "..");
    EXPECT_TRUE(fsutil::normpath("../") == "..");
    EXPECT_TRUE(fsutil::normpath("..\\") == "..");
    EXPECT_TRUE(fsutil::normpath("/.") == "\\");
    EXPECT_TRUE(fsutil::normpath("\\.") == "\\");

// TODO: also need Windows-specific shit...
//    EXPECT_EQ(fsutil::normpath("/.."), "/");
//    EXPECT_EQ(fsutil::normpath("/usr/bin"), "/usr/bin");
//    EXPECT_EQ(fsutil::normpath("/usr/bin/./.."), "/usr");
//    EXPECT_EQ(fsutil::normpath("./include"), "include");
//    EXPECT_EQ(fsutil::normpath("./../bin/include"), "../bin/include");
}



#endif
