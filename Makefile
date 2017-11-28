default: FoxtrotLogReader

# Compile main.cpp
main.o: main.cpp
	g++ -c main.cpp

# Compile
FoxtrotLogReader.o: FoxtrotLogReader.cpp
	g++ -c FoxtrotLogReader.cpp

# Link the object files into executable
FoxtrotLogReader: main.o FoxtrotLogReader.o
	g++ main.o FoxtrotLogReader.o -o FoxtrotLogReader

clean:
	rm -rf *o FoxtrotLogReader
