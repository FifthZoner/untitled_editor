cmake_minimum_required(VERSION 4.0)
project(untitled_editor)

set(CMAKE_CXX_STANDARD 23)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/modules/")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/modules/")
endif()

add_executable(
        ${PROJECT_NAME}
        src/main.cpp
        src/generated/version.hpp
        src/moduleManager/moduleManager.hpp
        src/startup/startup.hpp
        src/options.hpp
        src/errors/errors.hpp
        src/errors/errors.cpp
        src/errors/errors.cpp
        src/definitions.hpp
        src/startup/startup.cpp
        src/taskManager/taskManager.hpp
        src/taskManager/task.hpp
        src/taskManager/taskRunner.cpp
        src/taskManager/taskRunner.hpp
        src/taskManager/taskManager.cpp
        src/taskManager/taskManager.hpp
        src/taskManager/task.cpp
)

add_custom_target(
        TrackBuild ALL
        COMMAND python ../tracking/TrackBuild.py
        WORKING_DIRECTORY ../tracking/
        BYPRODUCTS ../src/generated/Version.hpp)

add_dependencies(${PROJECT_NAME} TrackBuild)
