#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "loop.h"


unsigned int WIDTH = 10, HEIGHT = 10, MINE_AMOUNT = 10;

void init_mine_map(bool mine_map[WIDTH][HEIGHT]) {
	unsigned int x, y, mine_amount = 0;

	while (true) {
		if (mine_amount >= MINE_AMOUNT) return;

		x = rand() % WIDTH;
		y = rand() % HEIGHT;

		if (mine_map[x][y] == true) continue;

		mine_map[x][y] = true;
		mine_amount++;
	}
}

void make_board(unsigned int game_board[WIDTH][HEIGHT], bool mine_map[WIDTH][HEIGHT]) {
	int dx[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	int dy[8] = { 0, 1, -1, 1, -1, 0, 1, -1 };
	int nx, ny, found = 0;

	for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGHT; j++) {
			if (mine_map[i][j]) {
				game_board[i][j] = '*';
				continue;
			}

			found = 0;
			for (int k=0; k<8; k++) {
				nx = i+dx[k];
				ny = j+dy[k];
				if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT) continue;
				if (mine_map[nx][ny]) found++;
			}
			game_board[i][j] = found;
		}
	}
}

int main() {
	unsigned int size;
	while (true) {
		printf("size mine_amount: ");
		scanf("%d %d", &size, &MINE_AMOUNT);
		if (MINE_AMOUNT > (size*size)/2) {
			printf("mine_amount <= (size^2)/2\n");
			continue;
		}
		break;
	}
	WIDTH = size;
	HEIGHT = size;
	srand(time(NULL));

	bool mine_map[WIDTH][HEIGHT];
	memset(mine_map, 0, sizeof(mine_map));
	init_mine_map(mine_map);

	unsigned int game_board[WIDTH][HEIGHT];
	memset(game_board, 0, sizeof(game_board));
	make_board(game_board, mine_map);

	char playing_board[WIDTH][HEIGHT];
	memset(playing_board, 35, sizeof(playing_board));
	for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGHT; j++) {
			playing_board[i][j] = 35;
		}
	}
	while (true) {
		loop(WIDTH, HEIGHT, game_board, playing_board);
		check_win(WIDTH, HEIGHT, playing_board, MINE_AMOUNT);
	}
	return 0;
}
