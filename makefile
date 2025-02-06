main: main.cpp
	gcc -Wall -Wextra $(shell pkg-config --cflags gtk4) -o main main.cpp $(shell pkg-config --libs gtk4) -lstdc++
test: main
	./main