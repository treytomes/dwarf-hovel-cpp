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
add_executable(DwarfHovel
    "src/main.cpp"

    "src/Color.cpp"
    "src/DemoGameState.cpp"
    "src/GameState.cpp"
    "src/GameStateManager.cpp"
    "src/gl_error.cpp"
    "src/gl_program.cpp"
    "src/gl_shader.cpp"
    "src/glew_error.cpp"
    "src/Logger.cpp"
	"src/MainMenuGameState.cpp"
    "src/OEM437.cpp"
    "src/sdl_error.cpp"
    "src/Settings.cpp"
    "src/system.cpp"
    "src/Texture.cpp"
    "src/UIButton.cpp"
    "src/UIElement.cpp"
	"src/UILabel.cpp"
    "src/Window.cpp"
)

target_include_directories(DwarfHovel PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

add_custom_target(copy_assets
    #COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/settings.json" "${CMAKE_CURRENT_BINARY_DIR}/settings.json"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/render.frag" "${CMAKE_CURRENT_BINARY_DIR}/render.frag"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/render.vert" "${CMAKE_CURRENT_BINARY_DIR}/render.vert"
)
add_dependencies(DwarfHovel copy_assets)

if (WIN32)
    add_custom_command(
        TARGET DwarfHovel POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:DwarfHovel>"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "C:/glew-2.1.0/bin/Release/x64/glew32.dll" "$<TARGET_FILE_DIR:DwarfHovel>/glew32.dll"
        VERBATIM
    )

endif()
