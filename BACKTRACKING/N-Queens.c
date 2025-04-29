#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 4

char board[N][N][3];  // Each cell holds strings like "Q1" + '\0'

bool is_safe(int row, int col) {
    for (int c = 0; c < N; c++) {
        if (strncmp(board[row][c], "Q", 1) == 0) return false;
    }
    for (int r = 0; r < N; r++) {
        if (strncmp(board[r][col], "Q", 1) == 0) return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (strncmp(board[i][j], "Q", 1) == 0) return false;
    }
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (strncmp(board[i][j], "Q", 1) == 0) return false;
    }
    return true;
}

void print_board() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%s\t", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void nqueens(int row) {
    if (row == N) {
        printf("All Queens are successfully placed!\n");
        print_board();
        return;
    }

    for (int j = 0; j < N; j++) {
        if (is_safe(row, j)) {
            sprintf(board[row][j], "Q%d", row + 1);  // Place "Q1", "Q2", ...
            nqueens(row + 1);
            strcpy(board[row][j], ".");  // Backtrack
        }
    }
}

int main() {
    // Initialize board with "."
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            strcpy(board[i][j], ".");

    nqueens(0);

    return 0;
}
