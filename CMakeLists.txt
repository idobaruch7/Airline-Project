cmake_minimum_required(VERSION 3.14)
project(AirlineProject)

set(CMAKE_CXX_STANDARD 17) # FTXUI requires at least C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Fetch Content to automatically download FTXUI
include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# Gather source files but EXCLUDE the main.cpp so we can create two separate targets
file(GLOB SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main_tui.cpp")

# Specify where to find header files
include_directories(${PROJECT_NAME} PUBLIC include)

# --- Target 1: The Original CLI App ---
add_executable(AirlineProject src/main.cpp ${SOURCES})
target_include_directories(AirlineProject PUBLIC include)

# --- Target 2: The New TUI App ---
add_executable(AirlineProject_TUI src/main_tui.cpp ${SOURCES})
target_include_directories(AirlineProject_TUI PUBLIC include)
target_link_libraries(AirlineProject_TUI PRIVATE ftxui::screen ftxui::dom ftxui::component)