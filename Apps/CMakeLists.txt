cmake_minimum_required (VERSION 2.6)
project (UnitTests)
# The version number.
# set (CText_VERSION_MAJOR 1)
# set (CText_VERSION_MINOR 0)

# Uncomment below to build and run in Unicode
# add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
# add the binary tree to the search path for include files
include_directories("${PROJECT_BINARY_DIR}")
 
add_executable(UnitTests UnitTests.cpp Main.cpp terminal.cpp)

add_subdirectory (Demos/CollectSentences)
add_subdirectory (Demos/PaddRightLines)
add_subdirectory (Demos/SortLines)
add_subdirectory (Demos/TrimLines)
add_subdirectory (Demos/WordFrequencies)
add_subdirectory (Demos/HighlightWords)
