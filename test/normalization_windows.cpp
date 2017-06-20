//  :copyright: (c) 2017 Alex Huszagh.
//  :license: MIT, see LICENSE.md for more details.

#if defined(_WIN32)                // WINDOWS

#include "config.h"

// TESTS
// -----


TEST(normalization, normpath)
{
    EXPECT_PATH_EQ(fsutil::normpath(L"."), L".");
    EXPECT_PATH_EQ(fsutil::normpath(L"./"), L".");
    EXPECT_PATH_EQ(fsutil::normpath(L".\\"), L".");
    EXPECT_PATH_EQ(fsutil::normpath(L"./.."), L"..");
    EXPECT_PATH_EQ(fsutil::normpath(L".\\.."), L"..");
    EXPECT_PATH_EQ(fsutil::normpath(L".."), L"..");
    EXPECT_PATH_EQ(fsutil::normpath(L"../"), L"..");
    EXPECT_PATH_EQ(fsutil::normpath(L"..\\"), L"..");
    EXPECT_PATH_EQ(fsutil::normpath(L"/."), L"\\");
    EXPECT_PATH_EQ(fsutil::normpath(L"\\."), L"\\");
    EXPECT_PATH_EQ(fsutil::normpath(L"/.."), L"\\");
    EXPECT_PATH_EQ(fsutil::normpath(L"\\.."), L"\\");
    EXPECT_PATH_EQ(fsutil::normpath(L"/usr/bin"), L"\\usr\\bin");
    EXPECT_PATH_EQ(fsutil::normpath(L"\\usr\\bin"), L"\\usr\\bin");
//    EXPECT_PATH_EQ(fsutil::normpath("/usr/bin/./.."), "/usr");
//    EXPECT_PATH_EQ(fsutil::normpath("./include"), "include");
//    EXPECT_PATH_EQ(fsutil::normpath("./../bin/include"), "../bin/include");
}



#endif
