include MakeColors

BUILD	:= build/

SOURCES := $(wildcard *.cpp)
OBJECTS := $(addsuffix .o,$(basename $(SOURCES)))
OBJECTS := $(addprefix $(BUILD),$(OBJECTS))

ADDITIONAL_LIB :=  -L ./lib
ADDITIONAL_H :=  -I ./include
LIBRARIES := -lGL -lGLEW -lglfw -lassimp -lSOIL2 -lIrrlicht


EXE := main

$(EXE): $(OBJECTS)
	$(call br)
	$(call printInfo, "Generating")
	$(call printWarning, $(EXE))
	$(call printInfo,"...")
	@g++ -o $@ $^ $(ADDITIONAL_LIB) $(LIBRARIES)
	$(call printObj,  "Finished!")
	$(call br)
	$(call br)


%.o: ../%.cpp
	$(call printInfo, "-Compiling")
	$(call printObj, $(notdir $^))
	@g++ -o $@ -c $^ $(ADDITIONAL_H)
	$(call printSuccess,  "[OK]")
	$(call br)

clean:
	$(call printWarning, "Borrando" "archivos" ".o...")
	$(call br)
	@rm -f $(OBJECTS)

init:
	./$(EXE)

info:
	$(info $(OBJECTS))
