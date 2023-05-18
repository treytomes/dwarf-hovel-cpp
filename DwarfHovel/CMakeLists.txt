cmake_minimum_required(VERSION 3.8)

project(DwarfHovel)

set(CMAKE_CXX_STANDARD 17) # Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2.
find_package(SDL2 REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLEW.

list(APPEND CMAKE_PREFIX_PATH "C:/glew-2.1.0")
find_package(GLEW REQUIRED)

# Set the include directories and link libraries
include_directories("./include" ${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY_DIRS})
link_libraries(${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

# Add your project executable here
add_executable(DwarfHovel "src/main.cpp" "include/logger.h" "src/logger.cpp" "include/config.h" "include/system.h" "src/system.cpp" "include/sdl_error.h" "src/sdl_error.cpp" "include/Window.h" "src/Window.cpp" "src/OEM437.cpp" "include/glew_error.h" "src/glew_error.cpp" "src/gl_shader.cpp" "include/gl_shader.h" "include/gl_program.h" "src/gl_program.cpp" "include/Texture.h" "src/Texture.cpp" "include/gl_error.h" "src/gl_error.cpp" "include/Color.h" "src/Color.cpp" "include/Tuple.h"  "include/Vector2UI.h" "include/IRenderContext.h" "include/OEM437.h" "include/moremath.h" "include/json.h")

add_custom_command(
        TARGET DwarfHovel POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/settings.json
                ${CMAKE_CURRENT_BINARY_DIR}/settings.json)

add_custom_command(
        TARGET DwarfHovel POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/render.frag
                ${CMAKE_CURRENT_BINARY_DIR}/render.frag)

add_custom_command(
        TARGET DwarfHovel POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/render.vert
                ${CMAKE_CURRENT_BINARY_DIR}/render.vert)

if (WIN32)
    add_custom_command(
        TARGET DwarfHovel POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:DwarfHovel>"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "C:/glew-2.1.0/bin/Release/x64/glew32.dll" "$<TARGET_FILE_DIR:DwarfHovel>/glew32.dll"
        VERBATIM
    )

endif()
