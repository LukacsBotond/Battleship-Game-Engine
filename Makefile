CFLAGS = -Wall -std=c++17 -g

game: ./src/*.cpp ./src/*.h
	g++ -o ./src/game ./src/*.cpp $(CFLAGS)

clean: 
	rm -f ./game