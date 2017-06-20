//  :copyright: (c) 2017 Alex Huszagh.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \brief Testing configurations for streamline builds.
 */

#include <fsutil.h>
#include <gtest/gtest.h>


#if defined(_WIN32)                 // WINDOWS

#define EXPECT_PATH_EQ(lhs, rhs)                                        \
    EXPECT_EQ(std::wstring(lhs), std::wstring(rhs));

#define EXPECT_PATH_NE(lhs, rhs)                                        \
    EXPECT_NE(std::wstring(lhs), std::wstring(rhs));

#else                               // LINUX

#define EXPECT_PATH_EQ(lhs, rhs)                                        \
    EXPECT_EQ(std::string(lhs), std::string(rhs));

#define EXPECT_PATH_NE(lhs, rhs)                                        \
    EXPECT_NE(std::string(lhs), std::string(rhs));

 #endif
