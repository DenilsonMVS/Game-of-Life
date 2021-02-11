
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define FIELD_WIDTH 430
#define FIELD_HEIGHT 120

#define ALIVE '#'
#define DEAD ' '


void printField(const char *field, int width, int height) {
	system("clear");
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++)
			printf("%c", field[i * width + j]);
		printf("\n");
	}
}


int numOfNeighbors(const char *field, int width, int height, int xPos, int yPos) {
	const int positions[8][2] = {
		{-1, -1},
		{0, -1},
		{1, -1},
		{-1, 0},
		{1, 0},
		{-1, 1},
		{0, 1},
		{1, 1}
	};

	int count = 0;

	for(int i = 0; i < 8; i++) {
		const int x = xPos + positions[i][0];
		const int y = yPos + positions[i][1];

		if(!(x < 0 || x >= width || y < 0 || y >= height))
			if(field[y * width + x] == ALIVE)
				count++;
	}

	return count;
}

void fieldLogic(const char *field, char *newField, int width, int height) {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			const int tmp = numOfNeighbors(field, width, height, j, i);
			
			if(field[i * width + j] == DEAD) {
				if(tmp == 3)							// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
					newField[i * width + j] = ALIVE;
				else
					newField[i * width + j] = DEAD;
			} else {
				if(tmp < 2 || tmp > 3)					// Any live cell with fewer than two live neighbours dies, as if by underpopulation. Any live cell with more than three live neighbours dies, as if by overpopulation.
					newField[i * width + j] = DEAD;
				else									// Any live cell with two or three live neighbours lives on to the next generation.
					newField[i * width + j] = ALIVE;
			}
		}
	}
}

int main() {
	srand(time(NULL));

	char field1[FIELD_HEIGHT][FIELD_WIDTH];
	char field2[FIELD_HEIGHT][FIELD_WIDTH];
	
	/* Generate random field */
	for(int i = 0; i < FIELD_HEIGHT; i++) {
		for(int j = 0; j < FIELD_WIDTH; j++) {
			if(rand() % 100 < 10)
				field1[i][j] = ALIVE;
			else
				field1[i][j] = DEAD;
		}
	}
	

	
	char *old = (char *) field1, *new = (char *) field2;
	while(true) {
		fieldLogic(old, new, FIELD_WIDTH, FIELD_HEIGHT);
		printField(new, FIELD_WIDTH, FIELD_HEIGHT);

		char *tmp = old;
		old = new;
		new = tmp;

		char c;
		scanf("%c", &c); 	// keep pressing ENTER to continue
		if(c == 'q') 		// to exit, press q
			break;
	}

	return 0;
}
