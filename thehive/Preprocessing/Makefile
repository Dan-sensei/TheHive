include MakeColors

BUILD	:= build/

SOURCES := $(shell find src/ -type f -name "*.cpp")
OBJECTS := $(patsubst %.cpp,%.o, $(SOURCES))
OBJECTS := $(addprefix $(BUILD),$(OBJECTS))

LIBRARIES := -lassimp

COMPILER := g++

EXE := BinaryFiles

build: $(EXE)

$(EXE): $(OBJECTS)
	$(call printWarning, "Preprocessing...")
	$(call br)
	@$(COMPILER) -o $@ $^ $(LIBRARIES)
	@./BinaryFiles
	$(call printObj,  "Done!")
	$(call br)
	$(call br)

$(OBJECTS): $(BUILD)%.o : %.cpp
	@mkdir -p ${@D}

	@$(COMPILER) -g -o $@ -c $<
	$(call printInfo, "-Compiling")
	$(call printObj, $^)
	$(call printSuccess,  "[OK]")
	$(call br)

clean:
	$(call printWarning, "Deleting" )
	$(call printObj,"BinaryFiles")
	$(call printWarning,"..." )
	@rm -rf $(BUILD)
	@rm -rf ./BinaryFiles
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
