default:
	gcc src/*.c -ggdb -Iinclude -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -DGRAPHICS_API_OPENGL_33 -o pong


#gcc -o exe src/main.c -I../raylib/src -L../raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
