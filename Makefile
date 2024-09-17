CC=clang
BIN_NAME=miner
VERSION=1

output: main.o loop.o
	$(CC) -o ./build/$(BIN_NAME)_$(VERSION) ./build/main.o ./build/loop.o

main.o:
	$(CC) -o ./build/main.o ./src/main.c -c

loop.o:
	$(CC) -o ./build/loop.o ./src/loop.c -c
