main: main.cpp
	gcc $(shell pkg-config --cflags gtk4 ) -o main main.cpp $(shell pkg-config --libs gtk4 )
test: main
	./main