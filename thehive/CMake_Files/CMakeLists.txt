cmake_minimum_required(VERSION 2.8)

set( PROJECT_NAME "TheHive-cmake" )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Nombre de proyecto
project(${PROJECT_NAME})

## Seleccionar todos los CPP
FILE(GLOB_RECURSE SRCS "../src/*.cpp" "../src/BT/*.cpp" "../src/Bullet/*.cpp" "../src/ComponentArch/*.cpp" "../src/ComponentArch/Components/*.cpp" "../src/ComponentArch/Components/Colliders/*.cpp" "../src/EventSystem/*.cpp" "../src/FMOD/*.cpp" "../src/GameAI/*.cpp" "../src/Omicron/*.cpp" "../src/Omicron/2D/*.cpp" "../src/Omicron/CORE/*.cpp" "../src/Omicron/FX/*.cpp" "../src/Omicron/ZMESHES/*.cpp" "../src/States/*.cpp")

# Directorio donde estan los Find[PACKAGE].cmake
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/" ${CMAKE_MODULE_PATH})

# Usando OpenGL no hay que anyadir ni GL ni GLU
# set( OpenGL_GL_PREFERENCE GLVND )
set( OpenGL_GL_PREFERENCE LEGACY )
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)

set( GLFW_LIBRARY /usr/lib/libglfw.so )
find_package(GLFW REQUIRED)

set( C_FMOD_LIBS /usr/lib/libfmod.so /usr/lib/libfmodL.so /usr/lib/libfmodstudio.so /usr/lib/libfmodstudioL.so )
set( FMOD_LIBRARY ${C_FMOD_LIBS} )
set( FMOD_EVENT_LIBRARY ${C_FMOD_LIBS} )
set( FMOD_DIR ../include/FMOD )
set( FMOD_INCLUDE_DIR ../include/FMOD )
set( FMOD_EVENT_INCLUDE_DIR ../include/FMOD )
set( FMOD_EVENT_NET_LIBRARY ${C_FMOD_LIBS})
find_package( FMOD REQUIRED )

find_package( Bullet REQUIRED )

## Definir el ejecutable y linkado de las librerias
add_executable(${PROJECT_NAME} ${SRCS})

include_directories(
	../src
	../include
	# /usr/include/bullet
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${GLUT_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
	${BULLET_INCLUDE_DIRS}
	${FMOD_INCLUDE_DIRS}
	${GLM_INCLUDE_DIR}
)

# Para tener distintos comandos que tienen el mismo target (Makefile)
set(ALLOW_DUPLICATE_CUSTOM_TARGETS TRUE)

# Anyadir el procesamiento de los objetos binarios antes de compilar
message("-- Added preprocessing make target to Makefile routine")
add_custom_target(Makefile
	COMMAND make
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Preprocessing/
)

# message("-- Added preprocessing clean target to Makefile routine")
# add_custom_target(Makefile
# 	COMMAND make clean
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Preprocessing/
# )

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${BULLET_LIBRARIES} /usr/lib/libBulletWorldImporter.so)
target_link_libraries(${PROJECT_NAME} ${FMOD_LIBRARIES})
