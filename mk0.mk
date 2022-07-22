CC=g++
CFLAGS=-c -Wall

SOURCES=3.cpp $\
		combinatorics.cpp distance.cpp $\
		alphabet.cpp sequence.cpp node.cpp interaction.cpp model.cpp multimodel.cpp $\
		print.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=3

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):  $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXECUTABLE)