# Project name and version
cmake_minimum_required(VERSION 3.10)
project(ges_locks VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Common compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")

# Debug build flags
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -DDEBUG")

# Release build flags
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Set default lock type to MCS if none specified
if(NOT SPIN_LOCK AND NOT TICKET_LOCK)
    set(MCS_LOCK TRUE)
endif()

# Create the library with the appropriate source file
if(SPIN_LOCK)
    add_library(ges_locks STATIC src/spin_lock.c src/ges_barrier.c)
elseif(TICKET_LOCK)
    add_library(ges_locks STATIC src/ticket_lock.c src/ges_barrier.c)
else()
    add_library(ges_locks STATIC src/mcs_lock.c src/ges_barrier.c)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(counter_test tests/counter_test.c)
target_link_libraries(counter_test PRIVATE ges_locks pthread)

# Installation rules
install(TARGETS ges_locks
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)
install(FILES include/ges_lock.h include/ges_barrier.h DESTINATION include)
