# aoc2025
Solutions for Advent of Code 2025 in C++.

## Initial Setup

- Clone repository: `git clone --recurse-submodules https://github.com/sanraith/aoc2025`
  - or `git submodule init` and `git submodule update` after git clone.
- To trigger bootstrapping of vcpkg, try building project using CMake or run
  - `./external/vcpkg/bootstrap-vcpkg.sh` on macOS/Linux
  - `.\external\vcpkg\bootstrap-vcpkg.bat` on Windows
- Update packages: `./external/vcpkg/vcpkg install`

## Adding packages

- Add package: `./external/vcpkg/vcpkg add port PACKAGE_NAME`
- Update packages: `./external/vcpkg/vcpkg install`
- Include package in CMakeLists.txt:
  ```cmake
  find_package(PACKAGE_NAME CONFIG REQUIRED)
  target_link_libraries(aoc2025lib PRIVATE PACKAGE_NAME::PACKAGE_NAME)
  ```

