include MakeColors

BUILD	:= build/

SOURCES := $(shell find src/ -type f -name "*.cpp" ! -path "src/Preprocessing/*")
OBJECTS := $(patsubst %.cpp,%.o, $(SOURCES))
OBJECTS := $(addprefix $(BUILD),$(OBJECTS))

ADDITIONAL_H :=  -I ./include -I ./src -I /usr/include/bullet -I /usr/include/opencv4
ADDITIONAL_LIB := -L ./lib
# -lopencv_core -lopencv_videoio
LIBRARIES := -lfmod -lfmodL -lfmodstudio -lopencv_core -lopencv_videoio -lfmodstudioL -lGLEW -lGL -lGLU -lglut -lglfw -lBulletCollision -lBullet3Common -lBulletDynamics -lLinearMath -lBullet3Geometry -lBulletWorldImporter -lBulletFileLoader -lBullet2FileLoader
COMPILER := g++ -std=c++17 -O3

EXE := main

build: preprocessing $(EXE)


preprocessing:
	cd Preprocessing && $(MAKE)

$(EXE): $(OBJECTS)
	$(call br)
	$(call printInfo, "Generating")
	$(call printWarning, $(EXE))
	$(call printInfo,"...")
	@$(COMPILER) -o $@ $^ $(ADDITIONAL_LIB) $(LIBRARIES)
	$(call printObj,  "Finished!")
	$(call br)
	$(call br)

$(OBJECTS): $(BUILD)%.o : %.cpp
	 @mkdir -p ${@D}

	@$(COMPILER) -g -o $@ -c $< $(ADDITIONAL_H)
	$(call printInfo, "-Compiling")
	$(call printObj, $^)
	$(call printSuccess,  "[OK]")
	$(call br)

clean:
	cd Preprocessing && $(MAKE) clean
	$(call printWarning, "Deleting" )
	$(call printObj,$(BUILD))
	$(call printWarning,"..." )
	@rm -rf $(BUILD)
	$(call printSuccess,  "[OK]")
	$(call br)
	$(call printWarning, "Deleting" )
	$(call printObj,$(EXE))
	@rm -f $(EXE)
	$(call printSuccess,  "[OK]")
	$(call br)

pre:
	cd Preprocessing && $(MAKE) clean
	make

init:
	./$(EXE)

molon:
	$(call br)
	$(call printObj, "Titulo:" )
	$(call printWarning,"THE" "HIVE")
	$(call br)
	$(call printObj, "Language:" )
	$(call printWarning,"C++")
	$(call br)
	$(call printObj, "Compiler:" )
	$(call printWarning,$(COMPILER))
	$(call br)
	$(call br)

info:
	$(call br)
	$(call printWarning, "Files:")
	$(call br)
	$(call br)
	$(call objColor)
	@$(foreach var,$(SOURCES), echo " "$(var); )
	$(call noColor)

	$(call br)

# WINDOWS
clcmake:
	rm -f TheHive-cmake.exe
	cd CMake_Files && rm -rf CMakeFiles && rm -f cmake_install.cmake && rm -f CMakeCache.txt && rm -f Makefile
	cd Preprocessing && rm -f WINBinaryFiles.exe
	cd Preprocessing/CMake_Files && rm -rf CMakeFiles && rm -f cmake_install.cmake && rm -f CMakeCache.txt && rm -f Makefile
	make clean

cmake:
	cd CMake_Files && cmake . -G "MSYS Makefiles"
	cd Preprocessing/CMake_Files && cmake . -G "MSYS Makefiles"

win:
	cd Preprocessing/CMake_Files && make -j4
	cd Preprocessing && ./WINBinaryFiles
	cd CMake_Files && make -j4
	./TheHive-cmake
