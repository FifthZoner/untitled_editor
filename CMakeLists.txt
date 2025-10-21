cmake_minimum_required(VERSION 4.0)
project(untitled_editor)

set(CMAKE_CXX_STANDARD 23)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/modules/")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/modules/")
endif()

add_executable(
        ${PROJECT_NAME}
        untitledEditor.hpp
        src/main.cpp
        src/settings.hpp
        src/definitions.hpp
        src/generated/version.hpp
        src/errors/errors.cpp
        src/errors/errors.hpp
        src/misc/vec2.tpp
        src/startup/startup.cpp
        src/startup/startup.hpp
        src/taskManager/task.cpp
        src/taskManager/task.hpp
        src/taskManager/taskRunner.cpp
        src/taskManager/taskRunner.hpp
        src/taskManager/taskManager.cpp
        src/taskManager/taskManager.hpp
        src/moduleManager/module.cpp
        src/moduleManager/module.hpp
        src/moduleManager/moduleManager.tpp
        interfaces/compositorInterface.hpp
        interfaces/interfaceMacro.hpp
)

file(GLOB COMPILED_MODULES modules/*)
message(STATUS "Module paths: ${COMPILED_MODULES}")
foreach (MODULE ${COMPILED_MODULES})
    if (EXISTS ${MODULE}/CMakeLists.txt AND EXISTS ${MODULE}/module.hpp AND EXISTS ${MODULE}/.manifest)
        set(CURRENT_MODULE "")
        cmake_path(GET MODULE STEM CURRENT_MODULE)
        message(STATUS "Found module: ${CURRENT_MODULE}")
        add_subdirectory(${MODULE} ${CMAKE_BINARY_DIR}/modules/${CURRENT_MODULE}/)
        get_filename_component(LIBRARY_NAME ${MODULE} NAME)

        if (DEFINED TARGET_LIBRARY_NAME)
            message(STATUS "Detected module library target: ${TARGET_LIBRARY_NAME}")
            add_dependencies(${PROJECT_NAME} ${TARGET_LIBRARY_NAME} )
        else()
            message(WARNING "No library target name defined in module: ${MODULE}")
        endif()
    endif()
endforeach()

add_custom_target(
        TrackBuild ALL
        COMMAND python ../tracking/TrackBuild.py
        WORKING_DIRECTORY ../tracking/
        BYPRODUCTS ../src/generated/Version.hpp)

add_dependencies(${PROJECT_NAME} TrackBuild)
