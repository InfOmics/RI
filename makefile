INCLUDES= -I ./rilib/ -I ./include/
CC=g++
CFLAGS=-c -O3

SOURCES= ri3.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ri36

all:	$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< $(INCLUDES) -o $@  
