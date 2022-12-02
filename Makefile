main: main.o snake.o
	g++ main.o snake.o -o main
main.o: main.cpp
	g++ -c main.cpp -o main.o
snake.o: snake.cpp snake.h
	g++ -c snake.cpp -o snake.o
clean:
	rm ./*.o main