# Linux (default)
CC=g++
TARGET = assignment
LDFLAGS = -lGL -lGLU -lglut
CFLAGS = -c -Wall

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
TARGET = assignment.exe
CFLAGS += -D_WIN32
endif

# OS X
ifeq "$(OSTYPE)" "darwin"
LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
CFLAGS += -D__APPLE__
endif

all:
	$(CC) $(CFLAGS) *.cpp -o $(TARGET) $(LDFLAGS)

clean:
	rm assignment *.exe