fsutil
======

High-level, cross-platform filesystem operations for C++.

[![Build Status](https://travis-ci.org/Alexhuszagh/fsutil.svg?branch=master)](https://travis-ci.org/Alexhuszagh/fsutil)
[![Build Status](https://tea-ci.org/api/badges/Alexhuszagh/fsutil/status.svg)](https://tea-ci.org/Alexhuszagh/fsutil)
[![Build status](https://ci.appveyor.com/api/projects/status/4fo9csmpuyugvg0o?svg=true)](https://ci.appveyor.com/project/Alexhuszagh/fsutil)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/12982/badge.svg)](https://scan.coverity.com/projects/alexhuszagh-fsutil)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/b75c01180aa14168b0baec9d77dca0ea)](https://www.codacy.com/app/Alexhuszagh/fsutil?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Alexhuszagh/fsutil&amp;utm_campaign=Badge_Grade)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Alexhuszagh/fsutil/blob/master/LICENSE.md)

**Table of Contents**

- [Design](#design)
- [Building](#building)
- [Portability](#portability)
- [Contributors](#contributors)
- [License](#license)

## Design

## Portability

fsutil requires `<experimental/filesystem>`, a proposed C++17 feature, requiring at minimum one of the following compilers:

- GCC 5.3
- Clang 3.9 (libstdc++ only)
- Visual Studio 14 2015 update 3

MinGW is currently not supported, as it has not yet fully implemented `<experimental/filesystem>`.

## Contributors

- Alex Huszagh

## License

The source code is distributed under the [MIT license](LICENSE.md).
