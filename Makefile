default: FoxtrotLogReader

# Compile main.cpp
main.o: main.cpp
	g++-7.2 -c main.cpp

# Compile
FoxtrotLogReader.o: FoxtrotLogReader.cpp Tools.h
	g++-7.2 -c FoxtrotLogReader.cpp

# Link the object files into executable
FoxtrotLogReader: main.o FoxtrotLogReader.o
	g++-7.2 main.o FoxtrotLogReader.o -o FoxtrotLogReader

clean:
	rm -rf *o FoxtrotLogReader
