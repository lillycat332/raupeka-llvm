cmake_minimum_required(VERSION 3.14...3.27)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Raupeka VERSION 0.1
	DESCRIPTION "Raupeka Compiler"
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -pthread")

add_compile_options(-Wall -Wextra -pedantic)

# Use boost for program options
find_package(Boost REQUIRED)

message(STATUS "Found Boost ${Boost_PACKAGE_VERSION}")
include_directories(${Boost_INCLUDE_DIRS})

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# The library code is here
add_subdirectory(src)
# The library headers are here
include_directories(include)

# The executable code is here
add_subdirectory(apps)
