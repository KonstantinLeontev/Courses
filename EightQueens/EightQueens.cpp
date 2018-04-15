#include <iostream>

// Fills a board with zeroes.
void fillBoard(int** board, const int &size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}
}

// Board output.
void printBoard(int** board, const int &size, int &varCnt) {
	std::cout << "\nSolution " << varCnt << '\n';
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << board[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

// Puts queen to the given place and marks others being attacked.
void putQueen(int** board, const int &size, int i, int j) {
	// Mark that place.
	board[i][j] = 1;

	// Mark all squares in the same column.
	for (int k = 0; k < size; k++) {
		board[k][j] = 1;
	}
	// Mark all squares in the same row.
	for (int m = 0; m < size; m++) {
		board[i][m] = 1;
	}

	// Mark diagonals.
	int k = i;
	int m = j;
	// To top-left.
	for (; k >= 0 && m >= 0; k--, m--) {
		board[k][m] = 1;
	}
	// To top-right.
	k = i; m = j;
	for (; k >= 0 && m < size; k--, m++) {
		board[k][m] = 1;
	}
	// To bottom-left.
	k = i; m = j;
	for (; k < size && m >= 0; k++, m--) {
		board[k][m] = 1;
	}
	// To bottom-right.
	k = i; m = j;
	for (; k < size && m < size; k++, m++) {
		board[k][m] = 1;
	}
}

// Finds the number of solutions.
void queenPuzzle(int** board, const int &size, int i, int queenCnt, int &varCnt) {
	// Solution case
	if (queenCnt == size) {
		varCnt++;
		queenCnt = 0;
		printBoard(board, size, varCnt);
	}
	// None solution case.
	else if (i != size) {
		for (int j = 0; j < size; j++) {
			if (!board[i][j]) {
				/*if (i == 0) {
					fillBoard(board, size);
				}*/
				putQueen(board, size, i, j);
				// Print to the screen.
				printBoard(board, size, varCnt);
				// And go to the next line.
				queenPuzzle(board, size, i + 1, queenCnt, varCnt);
			}
		}
	}	
}

int main() {
	bool run = true;
	int size{};

	// Main loop.
	while (run) {
		std::cout << "Input the size of the board (2 - 10) or 0 for quit: ";
		std::cin >> size;
		if (!size) {
			run = false;
		}
		else if (size < 2 || size > 10) {
			"Wrong input! Try again.\n";
		}
		else {
			// Make the array.
			int** board = new int *[size];
			for (int i = 0; i < size; i++) {
				board[i] = new int[size];
			}

			// Fill board with zeroes.
			fillBoard(board, size);

			// Variant's counter.
			int varCnt = 0;
			// Calculate the number of variants.
			queenPuzzle(board, size, 0, 0, varCnt);

			// Output the quantity of solutions.
			std::cout << varCnt << '\n';

			// Clean up.
			for (int i = 0; i < size; i++) {
				delete[] board[i];
			}
			delete[] board;
		}
	}
	return 0;
}