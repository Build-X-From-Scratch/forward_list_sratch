cmake_minimum_required(VERSION 3.16)

# Nama project
project(CppCrossPlatformTest
    VERSION 1.0.0
    DESCRIPTION "C++ Cross-Platform Testing Project"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags untuk debug dan release
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Platform specific settings
if(WIN32)
    # Windows specific settings
    add_compile_definitions(WIN32_LEAN_AND_MEAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
elseif(APPLE)
    # macOS specific settings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
elseif(UNIX)
    # Linux specific settings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    
    # Link pthread untuk threading di Linux
    find_package(Threads REQUIRED)
endif()

# Source files
set(SOURCES
    main.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries berdasarkan platform
if(UNIX AND NOT APPLE)
    # Linux - link pthread jika diperlukan
    target_link_libraries(${PROJECT_NAME} Threads::Threads)
elseif(APPLE)
    # macOS - tidak perlu pthread eksplisit
    message(STATUS "Building for macOS")
elseif(WIN32)
    # Windows - link library yang diperlukan
    message(STATUS "Building for Windows")
endif()

# Output info
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")

# Install target (opsional)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)