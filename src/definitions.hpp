//
// Created by fifthzoner on 12/10/2025.
//

#ifndef UNTITLED_EDITOR_DEFINITIONS_HPP
#define UNTITLED_EDITOR_DEFINITIONS_HPP

// if debug is on then we can add additional checks to see if things work correctly and catch errors early
#ifndef NDEBUG
#define BUILD_DEBUG
#define DebugArg(arg) , arg
#else
#define DebugArg(arg)
#endif

// a bit of an overgrown platform detection

#if defined(unix) or defined(__unix) or defined(__unix__)
#define TARGET_UNIX
#endif

#if defined(linux) or defined(__linux) or defined(__linux__)
#define TARGET_LINUX
#endif

#if defined(_WIN32) or defined(_WIN64) or defined(__CYGWIN__)
#define TARGET_WINDOWS
#endif

#if defined(__APPLE__) or defined(__MACH__)
#define TARGET_MACOSX
#endif

#if defined(__FreeBSD__)
#define TARGET_FREEBSD
#endif

#if defined(__ANDROID__)
#define TARGET_ANDROID
#endif

#endif //UNTITLED_EDITOR_DEFINITIONS_HPP