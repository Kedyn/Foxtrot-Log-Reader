default: FoxtrotLogReader

# Compile main.cpp
main.o: main.cpp
	g++ -c main.cpp -std=c++11

# Compile
FoxtrotLogReader.o: FoxtrotLogReader.cpp Tools.h
	g++ -c FoxtrotLogReader.cpp -std=c++11

# Link the object files into executable
FoxtrotLogReader: main.o FoxtrotLogReader.o
	g++ main.o FoxtrotLogReader.o -o FoxtrotLogReader -std=c++11

clean:
	rm -rf *o FoxtrotLogReader
