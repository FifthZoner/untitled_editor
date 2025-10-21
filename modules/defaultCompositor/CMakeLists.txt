set(LIBRARY_NAME untitled_editor_default_compositor)

message(STATUS "Configuring library: ${LIBRARY_NAME}")

add_library(
        ${LIBRARY_NAME}
        SHARED
        module.hpp
        src/compositor.cpp
        src/compositor.hpp
        src/window.cpp
        src/window.hpp
        src/windowFactory.cpp
        src/windowFactory.hpp
        src/module.cpp

)

target_link_libraries(${LIBRARY_NAME} PRIVATE SDL3)

set(TARGET_LIBRARY_NAME ${LIBRARY_NAME} PARENT_SCOPE)