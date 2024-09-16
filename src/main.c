#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 10
#define MINE_AMOUNT 30

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
	srand(time(NULL));

	bool mine_map[WIDTH][HEIGHT] = {0};
	init_mine_map(mine_map);

	unsigned int game_board[WIDTH][HEIGHT] = {0};
	make_board(game_board, mine_map);

	for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGHT; j++) {
			printf("%2d ", game_board[i][j]);
		}
		fputs("\n", stdout);
	}
	return 0;
}
