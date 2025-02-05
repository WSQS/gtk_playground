main:
	gcc $( pkg-config --cflags gtk4 ) -o main main.cpp $( pkg-config --libs gtk4 )