default:
	gcc src/*.c -ggdb -Wall -Iinclude -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o pong


#gcc -o exe src/main.c -I../raylib/src -L../raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
