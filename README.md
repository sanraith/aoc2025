# aoc2025

Solutions for Advent of Code 2025 in C++.

## Initial Setup

- Clone repository: `git clone --recurse-submodules https://github.com/sanraith/aoc2025`
  - or `git submodule init` and `git submodule update` after git clone.
- If not using CLion, make sure to set the vcpkg correctly. To use it from submodule, set:  
  `-DCMAKE_TOOLCHAIN_FILE=..\external\vcpkg\scripts\buildsystems\vcpkg.cmake`
- To trigger bootstrapping of vcpkg, try building project using CMake or run
  - `./external/vcpkg/bootstrap-vcpkg.sh` on macOS/Linux
  - `.\external\vcpkg\bootstrap-vcpkg.bat` on Windows

## Scaffolding boilerplate code for a new day

Scaffolding instructions are provided for the copilot agent in `.github/agents/Scaffolder.agent.md`
to auto-generate empty boilerplate code for each day. To use, ask in agent mode to `scaffold day 1`.  
While scaffolding, the agent tries to run `scaffold.cpp` to download puzzle description and input,
and tries to open the current puzzle description in the user's browser.
To allow this to work without user interaction, whitelist the following commands to auto-approve:

- Opening adventofcode.com:
  ```regex
  /^(Start-Process|open) 'https:\/\/adventofcode\.com\/\d+\/day\/\d+'$/
  ```
- Running scaffolder in debug mode:
  ```regex
  /^\.[\\\/]cmake-build-debug-(win|mac)[\\\/]scaffold(\.exe)?( -y \d+ -d \d+)?$/
  ```

## Running solutions

- Run a specific day: `aoc2025 -y 2025 -d 1` or `aoc2025 --year 2025 --day 1`
- Run the last implemented day: `aoc2025 -l` or `aoc2025 --last`
- Run all implemented days: `aoc2025 -a` or `aoc2025 --all`
- Show help: `aoc2025 -h` or `aoc2025 --help`

Configuration file:

- The runner automatically looks for `aoc2025.config.json` in the current directory or nearest parent directory.
- Example config (see `src/util/AocConfig.h` for details):

```json
{
  "eventYear": 2025,
  "copyResultToClipboard": true,
  "sessionCookie": "your_session_cookie_here"
}
```

## Adding packages

- Add package: `./external/vcpkg/vcpkg add port PACKAGE_NAME`
- Include package in CMakeLists.txt:
  ```cmake
  find_package(PACKAGE_NAME CONFIG REQUIRED)
  target_link_libraries(aoc2025lib PRIVATE PACKAGE_NAME::PACKAGE_NAME)
  ```


## Advent of Code Automation

This repository does follow the automation guidelines on the
/r/adventofcode [community wiki](https://www.reddit.com/r/adventofcode/wiki/faqs/automation). Specifically:

- Outbound calls are only triggered manually, by `scaffold.cpp`.
- All successful web requests are cached locally in `.cache/` by `CachedAocDataLoader`
- If you suspect your input is corrupted, you can manually request a fresh copy by deleting the corresponding file in
  first from `input/`, then `.cache/` if the problem persists.
- The User-Agent header in `CachedAocDataLoader` is set to me (
  `https://github.com/sanraith/aoc2025 by sanraith@users.noreply.github.com`) since I maintain this repository.
