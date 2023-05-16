cmake_minimum_required(VERSION 3.8)

project(DwarfHovel)


#set(CMAKE_CXX_STANDARD 11) # Set the C++ standard to C++11

set(CMAKE_CXX_STANDARD 17) # Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2.
find_package(SDL2 REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLEW.

list(APPEND CMAKE_PREFIX_PATH "C:/glew-2.1.0")

# GLEW directories - change according to your version and system
#set(GLEW_INCLUDE_DIR "C:/glew-2.1.0/include")
#set(GLEW_LIBRARY "C:/glew-2.1.0/lib/Release/x64/glew32.lib")

find_package(GLEW REQUIRED)

# Set the include directories and link libraries
include_directories(${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY_DIRS})
link_libraries(${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

file(COPY "render.frag" "render.vert" DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME})

#set_source_files_properties(main.cpp PROPERTIES OBJECT_DEPENDS "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/render.frag")
#set_source_files_properties(main.cpp PROPERTIES OBJECT_DEPENDS "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/render.vert")

# Add your project executable here
add_executable(DwarfHovel main.cpp "logger.h" "logger.cpp" "config.h" "system.h" "system.cpp" "sdl_error.h" "sdl_error.cpp" "window.h" "window.cpp" "glew_error.h" "glew_error.cpp" "gl_shader.cpp" "gl_shader.h" "gl_program.h" "gl_program.cpp" "texture.h" "texture.cpp" "gl_error.h" "gl_error.cpp")

add_custom_target(assets
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "render.frag" "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/render.frag"
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "render.vert" "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/render.vert"
	"render.frag" "render.vert"
)

add_custom_command(
	TARGET assets PRE_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "render.frag" "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/render.frag"
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "render.vert" "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/render.vert"
	VERBATIM
)
#add_dependencies(DwarfHovel "${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/render.frag")

if (WIN32)
    add_custom_command(
        TARGET DwarfHovel POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:DwarfHovel>"
        #COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:GLEW::GLEW>" "$<TARGET_FILE_DIR:DwarfHovel>"
        
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "C:/glew-2.1.0/bin/Release/x64/glew32.dll" "$<TARGET_FILE_DIR:DwarfHovel>/glew32.dll"
        VERBATIM
    )

endif()
