# \<untitled as of now\>

### Welcome to my questionable attempt at making a code/everything editor.

The idea is for this thing to be:
- fast - fastest possible loading and absolutely no prompts for user to wait;
- modular - every editor and refactor/suggestion tool as external libraries, loaded as needed;
- multithreaded - every action is done as a task handled by a core;
- transactional - every action returns a result that is then applied at once and cancelled on failure;
- exceptionless (hopefully) - errors are handled via std::expected and std::optional.

### Technologies:
- C++23
- probably SDL3
- CMake
- Python

### Why?
I got really annoyed with how slow, buggy, ancient and non-customizable Visual Studio (not vs code) is at work.