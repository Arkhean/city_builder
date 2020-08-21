# work in progress :)
CFLAGS= -g -O0

all:
	g++ ${CFLAGS} -c src/map.cpp -o build/map.o
	g++ ${CFLAGS} -c src/screen.cpp -o build/screen.o
	g++ ${CFLAGS} -c src/sprite.cpp -o build/sprite.o
	g++ ${CFLAGS} -c main.cpp -o build/main.o
	g++ ${CFLAGS} -o main build/*.o -lSDL2 -lSDL2_image -lSDL2_ttf
