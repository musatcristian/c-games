#default: // for static library in a local lib folder
#	gcc src/*.c -ggdb -Wall -Iinclude -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o pongexe

default: # for shared raylib installed in /usr/local
	gcc src/*.c -ggdb -Wall -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -o pongexe

#gcc -o exe src/main.c -I../raylib/src -L../raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
