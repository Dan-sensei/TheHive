BUILD	:= build/

SOURCES := $(wildcard *.cpp)
OBJECTS := $(addsuffix .o,$(basename $(SOURCES)))
OBJECTS := $(addprefix $(BUILD),$(OBJECTS))

ADDITIONAL_LIB :=  -L ./lib
ADDITIONAL_H :=  -I ./include
LIBRARIES := -lGL -lGLEW -lglfw -lassimp -lSOIL2



main: $(OBJECTS)
	g++ -o $@ $^ $(ADDITIONAL_LIB) $(LIBRARIES)
	./main

%.o: ../%.cpp
	g++ -o $@ -c $^	$(ADDITIONAL_H)

#clean:	$(shell rm ./build/*) main
clean:
	rm $(OBJECTS)

info:
	$(info $(EXTRA_O) $(ADDITIONAL_DIR) $(LIBRARIES))
