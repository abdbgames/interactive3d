# Linux (default)
CC=g++
TARGET=assignment
LDFLAGS=-lGL -lGLU -lglut -lm lib/libSOIL.a
CFLAGS=-Wall -Iinclude

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
TARGET=assignment.exe
CFLAGS+=-D_WIN32
endif

# OS X
ifeq ($(shell uname -s),Darwin)
LDFLAGS=-framework Carbon -framework OpenGL -framework GLUT
CFLAGS+=-D __APPLE__
endif

all:
	$(CC) $(CFLAGS) src/*.cpp -o $(TARGET) $(LDFLAGS)

clean:
	rm assignment *.exe
