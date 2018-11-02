BUILD	:= build/

SOURCES := $(wildcard *.cpp)
OBJECTS := $(addsuffix .o,$(basename $(SOURCES)))
OBJECTS := $(addprefix $(BUILD),$(OBJECTS))

ADDITIONAL_LIB :=  -L ./lib
ADDITIONAL_H :=  -I ./include
LIBRARIES := -lGL -lGLEW -lglfw -lassimp -lSOIL2



main: $(OBJECTS)
	g++ -o $@ $^ $(ADDITIONAL_LIB) $(LIBRARIES)

%.o: ../%.cpp
	g++ -o $@ -c $^	$(ADDITIONAL_H)

clean:
	rm -f $(BUILD)*.o


info:
	$(info $(EXTRA_O) $(ADDITIONAL_DIR) $(LIBRARIES))
