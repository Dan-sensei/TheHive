COMO COMPILAR CON CMAKE:
    WARNING: Antes de nada instala cmake (yaourt -S cmake)
    1. cd CMake_Files
    2. cmake .
    3. make
    4. cd .. && ./TheHive-cmake

ALIASES MOLONES:
    alias mkcmake="cd CMake_Files && cmake . && make -j4 && cd .."
    alias ccmake="cd CMake_Files && make clean && cd .."

IMPORTANTE:
    Al hacer push es bueno limpiar el cache que cmake ha generado:
        WARNING: ESTANDO EN LA CARPETA "CMake_Files" [!!!]
        alias clcmake="rm -rf CMakeFiles && rm -f cmake_install.cmake && rm -f CMakeCache.txt && rm -f Makefile && rm -f ../TheHive-cmake"

WARNING:
    [!!!] Hay que limpiar a mano los archivos del preprocessing! [!!!]
    cmake esta siendo utilizado para el port a Windows y primero habia que compilar el proyecto entero en Manjaro
