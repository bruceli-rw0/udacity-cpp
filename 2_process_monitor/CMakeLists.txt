cmake_minimum_required(VERSION 2.6)

project(monitor)

# Locate project prerequisites
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

# Add header files
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# Add project executable
add_executable(monitor ${SOURCES})

set_property(TARGET monitor PROPERTY CXX_STANDARD 17)
target_link_libraries(monitor ${CURSES_LIBRARIES})

# TODO: Run -Werror in CI.
target_compile_options(monitor PRIVATE -Wall -Wextra)
