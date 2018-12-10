include MakeColors

BUILD	:= build/
COMPONENTHEADERS:= src/ComponentArch/Components/ComponentHeaders.hpp
COMPONENTS := $(wildcard src/ComponentArch/Components/*.hpp)
COMPONENTS := $(subst src/,,$(COMPONENTS))

COMPONENTINITIALIZER:= src/ComponentArch/Components/ComponentInitializer
COMPONENTSCLASS := $(basename $(notdir $(COMPONENTS)))
COMPONENTSCLASS := $(subst ComponentHeaders,,$(COMPONENTSCLASS))


SOURCES := $(shell find src/ -type f -name "*.cpp")
OBJECTS := $(patsubst %.cpp,%.o, $(SOURCES))
OBJECTS := $(addprefix $(BUILD),$(OBJECTS))

ADDITIONAL_H :=  -I ./include -I ./src -I /usr/include/bullet
LIBRARIES := -lGL -lGLEW -lGLU -lglut -lglfw -lassimp -lIrrlicht -lBulletCollision -lBullet3Common -lBulletDynamics -lLinearMath -lBullet3Geometry -lBulletWorldImporter -lBulletFileLoader -lBullet2FileLoader

COMPILER := g++

EXE := main

build: PRE_BUILD $(EXE)

PRE_BUILD:
	@echo "void Factory::ComponentInitializer() {" > $(COMPONENTINITIALIZER)
	@for init in $(COMPONENTSCLASS) ; do echo "	$$init::initComponent();" >> $(COMPONENTINITIALIZER); done
	@echo "}" >> $(COMPONENTINITIALIZER)

$(EXE): $(OBJECTS)
	$(call br)
	$(call printInfo, "Generating")
	$(call printWarning, $(EXE))
	$(call printInfo,"...")
	@$(COMPILER) -o $@ $^ $(LIBRARIES)
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
	#@$(foreach var,$(SOURCES), echo " "$(var); )
	$(call noColor)

	$(call br)
