default: FoxtrotLogReader

# Compile main.cpp
main.o: main.cpp
	g++ -c main.cpp -std=c++11

Tools.o: Tools.h
	g++ -c Tools.cpp -std=c++11

DataRate.o: DataRate.h
	g++ -c DataRate.cpp -std=c++11

# Compile Main Class
FoxtrotLogReader.o: FoxtrotLogReader.cpp Tools.h Tools.o DataRate.h DataRate.o
	g++ -c FoxtrotLogReader.cpp -std=c++11

# Link the object files into executable
FoxtrotLogReader: main.o FoxtrotLogReader.o
	g++ main.o Tools.o DataRate.o FoxtrotLogReader.o -o FoxtrotLogReader -std=c++11

clean:
	rm -rf *o FoxtrotLogReader
