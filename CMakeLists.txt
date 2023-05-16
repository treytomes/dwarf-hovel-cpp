# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
list(APPEND CMAKE_PREFIX_PATH C:/SDL2/cmake)

project ("DwarfHovel")

# Include sub-projects.
add_subdirectory ("DwarfHovel")
