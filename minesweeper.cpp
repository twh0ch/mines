#include "minesweeper.hpp"

Minesweeper::Minesweeper(int rows, int cols, int numberOfMines)
    : rows(rows), cols(cols), numberOfMines(numberOfMines), board(rows, std::vector<Cell>(cols, Cell::Closed)), mines(rows, std::vector<int>(cols, 0)) {
    generateMines();
    calculateNumbers();
}

void Minesweeper::generateMines() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disRows(0, rows - 1);
    std::uniform_int_distribution<> disCols(0, cols - 1);

    for (int i = 0; i < numberOfMines; ++i) {
        int mineRow, mineCol;

        do {
            mineRow = disRows(gen);
            mineCol = disCols(gen);
        } while (mines[mineRow][mineCol] == -1);

        mines[mineRow][mineCol] = -1;
    }
}
void Minesweeper::calculateNumbers() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (mines[i][j] == -1) {
                continue;
            }

            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int ni = i + x;
                    int nj = j + y;
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && mines[ni][nj] == -1) {
                        mines[i][j]++;
                    }
                }
            }
        }
    }
}

void Minesweeper::openCell(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        std::cout << "Введите корректные координаты." << std::endl;
        return;
    }
    else if (board[row][col] != Cell::Closed){
        std::cout << "Вы это уже вводили." << std::endl;
        return;
    }

    if (mines[row][col] == -1) {
        std::cout << "Game Over! Вы попали в мину." << std::endl;
        board[row][col] = Cell::Open;
        printBoard(true);
        exit(0);
    } else {
        board[row][col] = Cell::Open;
    }
}

void Minesweeper::printBoard(bool showMines) const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == Cell::Open) {
                if (mines[i][j] == -1) {
                    if (showMines) {
                        std::cout << "* ";
                    } else {
                        std::cout << ". ";
                    }
                } else {
                    std::cout << mines[i][j] << " ";
                }
            } else if (board[i][j] == Cell::Closed) {
                std::cout << ". ";
            } else {
                std::cout << "F ";
            }
        }
        std::cout << std::endl;
    }
}



