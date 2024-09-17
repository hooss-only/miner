#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RESET_COLOR "\033[0m"
#define COORDINATE_COLOR "\033[33m"
#define NUMBER_COLOR "\033[37m"
#define BOMB_COLOR "\033[31m"
#define BLOCK_COLOR "\033[36m"

void print_board(int width, int height, char playing_board[width][height]) {
	fputs("  ", stdout);
	for (int i=0; i<width; i++) {
		printf("%s%d %s", COORDINATE_COLOR, i, RESET_COLOR);
	}

	fputs("\n", stdout);
	for (int i=0; i<height; i++) {
		printf("%s%d %s", COORDINATE_COLOR, i, RESET_COLOR);
		for (int j=0; j<width; j++) {
			if (playing_board[i][j] != '#' && playing_board[i][j] != '*') {
				printf("%s%d ", NUMBER_COLOR, playing_board[i][j]);
				continue;
			}
			char *color = BLOCK_COLOR;
			if (playing_board[i][j] == '*') color = BOMB_COLOR;

			printf("%s%c ", color, playing_board[i][j]);
			printf("%s", RESET_COLOR);
		}
		fputs("\n", stdout);
	}
}

void dfs(int width, int height, char playing_board[width][height], unsigned int game_board[width][height], int x, int y, bool visited[width][height]) {
  if (x < 0 || x >= width || y < 0 || y >= height || visited[x][y]) return;

  visited[x][y] = true;
	playing_board[x][y] = game_board[x][y];

	int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int nx, ny;
	if (game_board[x][y] == 0) {
		for (int k=0; k<8; k++) {
			nx = x+dx[k];
			ny = y+dy[k];
			dfs(width, height, playing_board, game_board, nx, ny, visited);
		}
	}
}

void check_win(int width, int height, char playing_board[width][height], unsigned int mine_amount) {
	unsigned int not_open = 0;
	for (int i=0; i<height; i++)
		for (int j=0; j<width; j++)
			if (playing_board[i][j] == '#') not_open++;

	if (not_open == mine_amount) {
		print_board(width, height, playing_board);
		fputs("YOU WIN!!!\n", stdout);
		exit(0);
	}
}

void loop(int width, int height, unsigned int game_board[width][height], char playing_board[width][height]) {
	print_board(width, height, playing_board);
	printf("X Y: ");

	unsigned int x, y;
	scanf("%d %d", &y, &x);

	if (x >= width || y >= height) return;
	if (game_board[x][y] == '*') {
		for (int i=0; i<height; i++) {
			for (int j=0; j<width; j++) {
				playing_board[i][j] = game_board[i][j];
			}
		}
		print_board(width, height, playing_board);
		fputs("GAME OVER!!\n", stdout);
		exit(0);
	}

	bool visited[width][height];
	memset(visited, false, sizeof(visited));
	if (game_board[x][y] == 0) {
		dfs(width, height, playing_board, game_board, x, y, visited);
	}

	playing_board[x][y] = game_board[x][y];
}
