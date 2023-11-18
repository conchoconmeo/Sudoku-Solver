#include <iostream>
#include <vector>

const int BOARD_SIZE = 9;

// Utility function to print the Sudoku board
void printBoard(const std::vector<std::vector<int>>& board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a number is safe to place in the board at a given position
bool isSafe(std::vector<std::vector<int>>& board, int row, int col, int num) {
    // Check the row and column for the same number
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid for the same number
    int startRow = row - (row % 3);
    int startCol = col - (col % 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Backtracking function to solve the Sudoku puzzle
bool solveSudoku(std::vector<std::vector<int>>& board) {
    // Find an empty cell (0 represents empty cell)
    int row = -1, col = -1;
    bool isEmpty = true;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty) {
            break;
        }
    }

    // If no empty cell found, the puzzle is solved
    if (isEmpty) {
        return true;
    }

    // Try placing numbers from 1 to 9 in the empty cell
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            // Recursively solve the puzzle
            if (solveSudoku(board)) {
                return true;
            }

            // If placing the number doesn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    return false; // No solution found for this cell
}

// Function to take user input for Sudoku puzzle
void takeInput(std::vector<std::vector<int>>& board) {
    std::string userInput;
    std::cout << "Enter the Sudoku puzzle (9x9 grid, use '0' for empty cells) or type 'Give Example' for an example:\n";
    std::cin >> userInput;

    if (userInput == "Give Example") {
        // Provide a default example Sudoku puzzle
        std::vector<std::vector<int>> exampleBoard = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        };

        board = exampleBoard;
    }
    else {
        // Read user input for Sudoku puzzle
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                std::cin >> board[i][j];
            }
        }
    }
}

// Function to solve the Sudoku puzzle (API entry point)
bool solveSudokuAPI(std::vector<std::vector<int>>& board) {
    return solveSudoku(board);
}

int main() {
    std::vector<std::vector<int>> sudokuBoard(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));

    takeInput(sudokuBoard);

    std::cout << "Sudoku Puzzle:" << std::endl;
    printBoard(sudokuBoard);

    if (solveSudokuAPI(sudokuBoard)) {
        std::cout << "\nSolution:" << std::endl;
        printBoard(sudokuBoard);
    }
    else {
        std::cout << "No solution exists for the given Sudoku puzzle." << std::endl;
    }

    return 0;
}