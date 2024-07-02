# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.1)

# project name
project(heston-alpaca)

# creates the variable EXEC and sets it to main
set(EXEC main)

# set the C++14 standard
set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(includes)

# Find libcurl package
find_package(CURL REQUIRED)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*.cpp)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${EXEC} ${SOURCES})

# Link libcurl to the executable
target_link_libraries(${EXEC} ${CURL_LIBRARIES})
