all:
	g++ main.cpp -o main.exe -I/usr/include/raylib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
