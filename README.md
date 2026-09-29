# TaskSequencer

Lightweight C++ task sequencing with concurrent execution, blocking, and join/barrier semantics. Requires C++17 or later. The library is header only.

## Build the example

From the repository root:

```sh
cmake -S . -B build
cmake --build build --config Release
```

Run on Linux/macOS with `./build/tasksequencer_example`. For Visual Studio on Windows, run `build\Release\tasksequencer_example.exe` from PowerShell (or open the generated solution and run the example target).

## Use in another CMake project

```cmake
add_subdirectory(path/to/TaskSequencer)
target_link_libraries(your_target PRIVATE TaskSequencer::TaskSequencer)
```

Include `Command.h` and `CommandController.h`, derive from `hex::CommandController`, enqueue a `hex::Command` using the protected `push()`, and call `nextCmd()->get().execute()` during your update loop. Each command must call `ends()` when its work completes. See [`test-main/main.cpp`](test-main/main.cpp) for a minimal working example.

To build without the example, configure with `-DTASKSEQUENCER_BUILD_EXAMPLE=OFF`.
