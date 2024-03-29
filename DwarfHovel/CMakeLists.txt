﻿cmake_minimum_required(VERSION 3.8)

project(DwarfHovel)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(NOT UNIX AND NOT APPLE)
	set(WIN32 TRUE)
endif()

set(CMAKE_CXX_STANDARD 17) # Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2.
find_package(SDL2 REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLEW.

list(APPEND CMAKE_PREFIX_PATH "C:/glew-2.2.0")
find_package(GLEW REQUIRED)

# Set the include directories and link libraries
include_directories("./include" ${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY_DIRS})
link_libraries(${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

# Add your project executable here
add_executable(DwarfHovel
    "src/main.cpp"

	"src/io/Logger.cpp"
	"src/io/Settings.cpp"

	"src/ui/UIButton.cpp"
    "src/ui/UIElement.cpp"
	"src/ui/UILabel.cpp"
	
    "src/states/CharacterTestState.cpp"
    "src/states/DemoGameState.cpp"
    "src/states/GameState.cpp"
    "src/states/GameStateManager.cpp"
	"src/states/MainMenuGameState.cpp"
	"src/states/MapTestState.cpp"
	"src/states/SoundFXGameState.cpp"
	
	"src/gl_error.cpp"
	"src/gl_program.cpp"
	"src/gl_shader.cpp"
	"src/glew_error.cpp"
	"src/sdl_error.cpp"

	"src/bitmap_templates.cpp"
    "src/bitmaps.cpp"
	"src/map_tiles.cpp"
	"src/Map.cpp"
	"src/MapTile.cpp"
    "src/OEM437.cpp"
    "src/System.cpp"
    "src/Texture.cpp"
    "src/Window.cpp"
)

target_include_directories(DwarfHovel PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/settings.json" "${CMAKE_CURRENT_BINARY_DIR}/settings.json"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/render.frag" "${CMAKE_CURRENT_BINARY_DIR}/render.frag"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/render.vert" "${CMAKE_CURRENT_BINARY_DIR}/render.vert"
)
add_dependencies(DwarfHovel copy_assets)

if (WIN32)
    add_custom_command(
        TARGET DwarfHovel POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:DwarfHovel>"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "C:/glew-2.2.0/bin/Release/x64/glew32.dll" "$<TARGET_FILE_DIR:DwarfHovel>/glew32.dll"


		VERBATIM
    )

endif()
