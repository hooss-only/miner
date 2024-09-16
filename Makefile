CC=clang
BIN_NAME=miner
VERSION=1

output: main.o
	$(CC) -o ./build/$(BIN_NAME)_$(VERSION) ./build/main.o

main.o:
	$(CC) -o ./build/main.o ./src/main.c -c
