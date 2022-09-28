CC = g++
CCFLAGS = -g -Wall

ifeq ($(OS),Windows_NT)
	PLATFORM := Windows
	TARGET := wordgrid.exe
	EXECUTABLE := $(TARGET)
else
	PLATFORM := $(shell uname -s)
	TARGET := wordgrid
	EXECUTABLE := ./$(TARGET)
endif

ifeq ($(PLATFORM),Windows)
	# TODO
	LIBS +=
endif
ifeq ($(PLATFORM),Linux)
	LIBS += -lGLU -lGL -lglut -lSDL2
endif
ifeq ($(PLATFORM),Darwin)
	LIBS += -framework GLUT -framework OpenGL -lSDL2
endif

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)
# SDL2 Audio
HEADERS += $(wildcard sdl2_audio/*.h)
OBJECTS += $(patsubst %.c, %.o, $(wildcard sdl2_audio/*.c))

.PHONY: default all clean

default: $(TARGET)
all: default

%.o: %.c %.cpp $(HEADERS)
	$(CC) $(CCFLAGS) -c $< $(LIBS) -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LIBS) -o $@

run:
	$(EXECUTABLE)

clean:
	-rm *.o
	-rm sdl2_audio/*.o
	-rm $(TARGET)
