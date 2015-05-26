# Linux (default)
CC=g++
TARGET=assignment
LDFLAGS=-lGL -lGLU -lglut
CFLAGS=-Wall -Iinclude

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
TARGET=assignment.exe
CFLAGS+=-D_WIN32

# OS X
else ifeq ($(shell uname -s),Darwin)
LDFLAGS=-framework Carbon -framework OpenGL -framework GLUT -lm lib/osxlibSOIL.a
CFLAGS+=-D __APPLE__

# Here we need to add libSOIL
else
LDFLAGS+=-lm lib/libSOIL.a
endif

all:
	$(CC) $(CFLAGS) src/*.cpp -o $(TARGET) $(LDFLAGS)

clean:
	rm assignment *.exe
