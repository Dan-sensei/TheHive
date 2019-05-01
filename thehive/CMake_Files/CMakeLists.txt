# WINDOWS COMPILATION ->	cmake . -G "MSYS Makefiles" -DWIN_COMPILATION=ON 
# MANJARO COMPILATION ->	cmake . -G "MSYS Makefiles" 

cmake_minimum_required(VERSION 2.8)

set( PROJECT_NAME "TheHive-cmake" )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-lstdc++fs" )
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Nombre de proyecto
project(${PROJECT_NAME})

# Seleccionar todos los CPP
FILE(GLOB_RECURSE SRCS 
	"../src/*.cpp"
	"../src/BT/*.cpp"
	"../src/Bullet/*.cpp"
	"../src/ComponentArch/*.cpp"
	"../src/ComponentArch/Components/*.cpp"
	"../src/ComponentArch/Components/Colliders/*.cpp"
	"../src/EventSystem/*.cpp"
	"../src/FMOD/*.cpp"
	"../src/GameAI/*.cpp"
	"../src/Omicron/*.cpp"
	"../src/Omicron/2D/*.cpp"
	"../src/Omicron/CORE/*.cpp"
	"../src/Omicron/FX/*.cpp"
	"../src/Omicron/ZMESHES/*.cpp"
	"../src/States/*.cpp"
)

# Directorio donde estan los Find[PACKAGE].cmake
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/" ${CMAKE_MODULE_PATH})

if(NOT DEFINED WIN_COMPILATION)
	set(WIN_COMPILATION "OFF")
endif(NOT DEFINED WIN_COMPILATION)

message("")
message("-- -------------------------------- --")
message("-- INITIALIZING WINDOWS COMPILATION --")
message("-- -------------------------------- --")

set( MINGW_LIBRARY_PATH "C:/MinGW/mingw32/lib" )
set( THEHIVE_INCLUDE_PATH ../include )

# Usando OpenGL no hay que anyadir ni GL ni GLU
set( OpenGL_GL_PREFERENCE GLVND )
find_package(OpenGL REQUIRED)

set( GLEW_INCLUDE_DIR  	${THEHIVE_INCLUDE_PATH}/GL )
set( GLEW_LIBRARY 		glew32.lib glew32s.lib)
find_package(GLEW REQUIRED)

set( GLM_INCLUDE_DIR  	${THEHIVE_INCLUDE_PATH} )
find_package(GLM REQUIRED)

set( GLFW_INCLUDE_DIR	${THEHIVE_INCLUDE_PATH}/GLFW )
set( GLFW_LIBRARY 		glfw3.dll)
find_package(GLFW REQUIRED)

set( WIN_FMOD_LIBS libfmod.a libfmodL.a libfmodstudio.a libfmodstudioL.a )
set( FMOD_LIBRARY 			${WIN_FMOD_LIBS} )
set( FMOD_EVENT_LIBRARY 	${WIN_FMOD_LIBS} )
set( FMOD_EVENT_NET_LIBRARY ${WIN_FMOD_LIBS} )
set( FMOD_DIR 				${THEHIVE_INCLUDE_PATH}/FMOD )
set( FMOD_INCLUDE_DIR 		${THEHIVE_INCLUDE_PATH}/FMOD )
set( FMOD_EVENT_INCLUDE_DIR ${THEHIVE_INCLUDE_PATH}/FMOD )
find_package( FMOD REQUIRED )

# set( BULLET_DYNAMICS_LIBRARY  	BulletDynamics.lib )
# set( BULLET_COLLISION_LIBRARY  	BulletCollision.lib )
# set( BULLET_MATH_LIBRARY  		LinearMath.lib )
# set( BULLET_SOFTBODY_LIBRARY  	BulletSoftBody.lib )
set( BULLET_INCLUDE_DIR 		${THEHIVE_INCLUDE_PATH}/BULLET/src ${THEHIVE_INCLUDE_PATH}/BULLET/Extras/Serialize )
find_package( Bullet REQUIRED )

message("-- Linking directories to ${CMAKE_CURRENT_SOURCE_DIR}/../lib root")
link_directories( 	${CMAKE_CURRENT_SOURCE_DIR}/../lib/WIN ${CMAKE_CURRENT_SOURCE_DIR}/../lib/ )

# Definir el ejecutable y linkado de las librerias
add_executable(${PROJECT_NAME} ${SRCS})

include_directories(
	../src
	../include
	../include/BULLET
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
	${BULLET_INCLUDE_DIRS}
	${FMOD_INCLUDE_DIRS}
	${GLM_INCLUDE_DIR}
)

# Anyadir el procesamiento de los objetos binarios antes de compilar
# message("-- Added preprocessing make target to Makefile routine")
# add_custom_target(Makefile
# 	COMMAND make
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Preprocessing/
# )

# message("-- Added preprocessing clean target to Makefile routine")
# add_custom_target(Makefile
# 	COMMAND make clean
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Preprocessing/
# )

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})

set(BULLET_LIBRARIES 
	libBulletWorldImporter.a
# 	libBullet2FileLoader.a
	libBulletFileLoader.a
	libBullet3Common.a
	libBullet3Geometry.a
	${BULLET_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} ${BULLET_LIBRARIES} )
target_link_libraries(${PROJECT_NAME} ${FMOD_LIBRARIES})

message("-- var=WIN_COMPILATION set free")
unset(WIN_COMPILATION CACHE)

# #############################
# Preprocessing
# #############################
# add_subdirectory(../Preprocessing/CMake_Files)