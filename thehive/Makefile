include MakeColors

BUILD	:= build/

SOURCES := $(shell find src/ -type f -name "*.cpp" ! -path "src/Preprocessing/*")
OBJECTS := $(patsubst %.cpp,%.o, $(SOURCES))
OBJECTS := $(addprefix $(BUILD),$(OBJECTS))

ADDITIONAL_H :=  -I ./include -I ./src -I /usr/include/bullet -I /usr/include/opencv4
ADDITIONAL_LIB := -L ./lib
# -lopencv_core -lopencv_videoio
LIBRARIES := -lopencv_core -lopencv_videoio -lfmod -lfmodL -lfmodstudio -lfmodstudioL -lGLEW -lGL -lGLU -lglut -lglfw -lBulletCollision -lBullet3Common -lBulletDynamics -lLinearMath -lBullet3Geometry -lBulletWorldImporter -lBulletFileLoader -lBullet2FileLoader
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
