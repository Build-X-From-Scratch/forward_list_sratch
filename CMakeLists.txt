cmake_minimum_required(VERSION 3.16)

# Nama project
project(ForwardListProject
    VERSION 1.0.0
    DESCRIPTION "Forward List Implementation Project"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/header)

# Compiler flags
if(WIN32)
    # Windows with MSVC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
else()
    # Linux/macOS with GCC/Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

# Collect source files
file(GLOB_RECURSE HEADER_FILES "header/*.hpp" "header/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "implementation/*.cpp")

# Debug: print found files
message(STATUS "=== Project Structure ===")
message(STATUS "Header files found:")
foreach(header ${HEADER_FILES})
    message(STATUS "  ${header}")
endforeach()
message(STATUS "Source files found:")
foreach(source ${SOURCE_FILES})
    message(STATUS "  ${source}")
endforeach()

# Create library if we have source files
if(SOURCE_FILES)
    # Create static library
    add_library(forward_list_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
    target_include_directories(forward_list_lib PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/header>
        $<INSTALL_INTERFACE:include>
    )
    
    # Link threads on Linux
    if(UNIX AND NOT APPLE)
        find_package(Threads REQUIRED)
        target_link_libraries(forward_list_lib PUBLIC Threads::Threads)
    endif()
    
    message(STATUS "Created library: forward_list_lib")
else()
    message(STATUS "No source files found - header-only library")
endif()

# Look for demo/example files to create executables
file(GLOB DEMO_FILES "*.cpp" "demo/*.cpp" "example/*.cpp" "test/*.cpp")

if(DEMO_FILES)
    message(STATUS "Demo/example files found:")
    foreach(demo ${DEMO_FILES})
        get_filename_component(demo_name ${demo} NAME_WE)
        message(STATUS "  Creating executable: ${demo_name}")
        add_executable(${demo_name} ${demo})
        
        # Include header directory
        target_include_directories(${demo_name} PRIVATE ${CMAKE_SOURCE_DIR}/header)
        
        # Link library if exists
        if(SOURCE_FILES)
            target_link_libraries(${demo_name} forward_list_lib)
        endif()
        
        # Link threads on Linux
        if(UNIX AND NOT APPLE)
            find_package(Threads REQUIRED)
            target_link_libraries(${demo_name} Threads::Threads)
        endif()
    endforeach()
else()
    # Create simple test executable to verify compilation
    message(STATUS "No demo files found - creating compilation test")
    
    file(WRITE ${CMAKE_BINARY_DIR}/test_compile.cpp
        "#include <iostream>\n"
        "#ifdef __has_include\n"
        "#if __has_include(\"forward_list.hpp\")\n"
        "#include \"forward_list.hpp\"\n"
        "#define HAS_FORWARD_LIST\n"
        "#endif\n"
        "#endif\n"
        "\n"
        "int main() {\n"
        "    std::cout << \"Forward List Project Compilation Test\" << std::endl;\n"
        "    \n"
        "    #ifdef _WIN32\n"
        "        std::cout << \"Platform: Windows\" << std::endl;\n"
        "    #elif __APPLE__\n"
        "        std::cout << \"Platform: macOS\" << std::endl;\n"
        "    #elif __linux__\n"
        "        std::cout << \"Platform: Linux\" << std::endl;\n"
        "    #endif\n"
        "    \n"
        "    #ifdef HAS_FORWARD_LIST\n"
        "        std::cout << \"✅ forward_list.hpp found and included\" << std::endl;\n"
        "    #else\n"
        "        std::cout << \"ℹ️  forward_list.hpp not found or not included\" << std::endl;\n"
        "    #endif\n"
        "    \n"
        "    std::cout << \"Compilation test passed successfully!\" << std::endl;\n"
        "    return 0;\n"
        "}\n"
    )
    
    add_executable(test_compile ${CMAKE_BINARY_DIR}/test_compile.cpp)
    target_include_directories(test_compile PRIVATE ${CMAKE_SOURCE_DIR}/header)
    
    if(SOURCE_FILES)
        target_link_libraries(test_compile forward_list_lib)
    endif()
    
    if(UNIX AND NOT APPLE)
        find_package(Threads REQUIRED)
        target_link_libraries(test_compile Threads::Threads)
    endif()
endif()

# Set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Output informasi
message(STATUS "=== Build Configuration ===")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Output Directory: ${CMAKE_SOURCE_DIR}/bin")

# Install configuration
if(SOURCE_FILES)
    install(TARGETS forward_list_lib
        EXPORT ForwardListTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )
endif()

install(FILES ${HEADER_FILES} DESTINATION include)

# Create package config
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "ForwardListConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)