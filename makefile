main: main.cpp
	gcc -Wall -Wextra $(shell pkg-config --cflags gtk4) -o main main.cpp $(shell pkg-config --libs gtk4) -std=c++23 -lstdc++
test: main
	./main