SOURCES := $(wildcard *.cpp)
#subst SUSTITUYE
OBJECTS := $(subst .cpp,.o,$(SOURCES))

#mv $(OBJECTS) build
ejecutable: $(OBJECTS)
	g++ -o $@ $^

#GENERALIZACION PARA CUALQUIER .o
#PARA ESTE CASO! CADA .o DEPENDE DE SOLO UN .cpp QUE SE LLAMA IGUAL
%.o: %.cpp
	g++ -o $@ -c $^

clean:
	@rm $(OBJECTS)

#COMO UN ECHO/PRINT
#LLAMARLO COMO make info
info:
	$(info $(SOURCES))
	$(info $(OBJECTS))

init:
	./ejecutable
