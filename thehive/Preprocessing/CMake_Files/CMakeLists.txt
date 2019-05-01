# ONLY WINDOWS!

cmake_minimum_required(VERSION 2.8)

set( PROJECT_NAME "WINBinaryFiles" )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -lassimp")

# Nombre de proyecto/ejecutable
project(${PROJECT_NAME})

# CPP
FILE(GLOB_RECURSE SRCS "../src/*.cpp")

# Directorio donde estan los Find[PACKAGE].cmake
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/" ${CMAKE_MODULE_PATH})

# Inclusion de librerias
set(ASSIMP_INCLUDE_DIR ../include/assimp)
set(ASSIMP_LIBRARIES libassimp.a)
# set(ASSIMP_LIBRARIES libassimp.dll)
find_package(ASSIMP REQUIRED)

add_executable(${PROJECT_NAME} ${SRCS})

include_directories(
	../src
	../include
	../include/assimp
	${ASSIMP_INCLUDE_DIR}
)

message(${ASSIMP_INCLUDE_DIR})
message(${ASSIMP_LIBRARY})

# target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARY})
target_link_libraries(${PROJECT_NAME} libassimp.a libassimp.dll libassimp.dll.a)