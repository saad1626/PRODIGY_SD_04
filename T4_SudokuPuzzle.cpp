#include <iostream>
using namespace std;

const int N = 9;

// Function to print the solved Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if the given number is safe to place at the given position
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number is not already present in the current row
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check if the number is not already present in the current column
    for (int y = 0; y < N; y++) {
        if (grid[y][col] == num) {
            return false;
        }
    }

    // Check if the number is not already present in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true; // If the number is safe to place
}

// Function to solve the Sudoku puzzle recursively using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Find the first empty cell (with value 0)
    bool isEmpty = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    // If there are no empty cells, the puzzle is solved
    if (!isEmpty) {
        return true;
    }

    // Try numbers 1 to 9 in the current empty cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num; // Place the number if it's safe

            // Recursively solve the puzzle
            if (solveSudoku(grid)) {
                return true; // If a solution is found, return true
            }

            grid[row][col] = 0; // Backtrack if no solution is found
        }
    }

    return false; // Return false if no solution is found
}

int main() {
    int grid[N][N];
    
    cout << "Enter the Sudoku puzzle grid (use 0 to represent empty cells):" << endl;
    for (int row = 0; row < N; row++) {
        cout<<"row #" <<row+1<<endl;
        for (int col = 0; col < N; col++) {
            cin >> grid[row][col];
        }
    }

    if (solveSudoku(grid)) {
        cout << "\nSudoku puzzle solved successfully:\n" << endl;
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for the given Sudoku puzzle." << endl;
    }

    return 0;
}
