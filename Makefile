CC=g++
CFLAGS=-c -Wall -std=c++11 
LDFLAGS=-Iopenal/include -Lopenal/lib -Wl,-rpath,"openal/lib" -lopenal -lalut -lm -lglut -lGLU -lGL 
SOURCES=geometry.cpp sound.cpp lighting.cpp particle.cpp build.cpp camera.cpp firework.cpp main.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=firework

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf *o $(EXECUTABLE)
