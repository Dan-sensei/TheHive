include MakeColors

BUILD	:= build/

SOURCES := $(shell find src/ -type f -name "*.cpp")

OBJECTS := $(patsubst %.cpp,%.o, $(SOURCES))
OBJECTS := $(addprefix $(BUILD),$(OBJECTS))

ADDITIONAL_LIB :=  -L ./lib
ADDITIONAL_H :=  -I ./include -I ./src
LIBRARIES := -lGL -lGLEW -lglfw -lassimp -lSOIL2 -lIrrlicht

COMPILER := g++

EXE := main

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

	$(call printInfo, "-Compiling")
	$(call printObj, $^)
	@$(COMPILER) -o $@ -c $< $(ADDITIONAL_H)
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

info:
	$(call br)
	$(call printObj, "Linker:" )
	$(call printWarning,$(COMPILER))
	$(call br)
	$(call br)
