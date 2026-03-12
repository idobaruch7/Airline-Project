cmake_minimum_required(VERSION 3.10)
project(AirlineProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Automatically find all .cpp files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Specify where to find header files
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Add a simple test target
# add_executable(test_runner test_runner.cpp)