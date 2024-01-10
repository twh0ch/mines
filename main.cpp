#include <iostream>
#include <vector>
#include <random>
#include <functional>

class Minesweeper {
public:
    Minesweeper(int rows, int cols, int numberOfMines)
        : rows(rows), cols(cols), numberOfMines(numberOfMines), board(rows, std::vector<Cell>(cols, Cell::Closed)), mines(rows, std::vector<int>(cols, 0)) {
        generateMines();
        calculateNumbers();
    }

    void printBoard(bool showMines = false) const {
        int k = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] == Cell::Open) {
                    if (mines[i][j] == -1) {
                        if (showMines) {
                            std::cout << "* ";
                        } else {
                            std::cout << "X ";
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

    void openCell(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != Cell::Closed) {
            return;
        }

        board[row][col] = Cell::Open;

        if (mines[row][col] == 0) {
            // Если открываем пустую ячейку, открываем все соседние пустые ячейки
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    openCell(row + i, col + j);
                }
            }
        }
    }

private:
    enum class Cell { Closed, Open, Flag };

    int rows;
    int cols;
    double minePercentage;
    std::vector<std::vector<Cell> >board;
    std::vector<std::vector<int> > mines;

   int numberOfMines;  // Новая переменная для хранения количества мин

    void generateMines() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> disRows(0, rows - 1);
        std::uniform_int_distribution<> disCols(0, cols - 1);

        for (int i = 0; i < numberOfMines; ++i) {
            int mineRow, mineCol;

            do {
                mineRow = disRows(gen);
                mineCol = disCols(gen);
            } while (mines[mineRow][mineCol] == -1);  // Проверяем, что в выбранной ячейке еще нет мины

            mines[mineRow][mineCol] = -1;  // Устанавливаем мину
        }
    }
    void calculateNumbers() {
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
};

int main() {
    
    int rows, cols, numberOfMines;
    int count = 0;
    
    std::cout << "Введите размеры поля (строки и столбцы): ";
    std::cin >> rows >> cols;

    std::cout << "Введите количество мин: ";
    std::cin >> numberOfMines;
    if(numberOfMines> rows * cols){
        std::cout<< "это невозможно" << std::endl;
        exit(1);
    }

    Minesweeper minesweeper(rows, cols, numberOfMines);

    std::cout << "Поле для игры в сапёра:" << std::endl;
    minesweeper.printBoard();
    
    while(true){
        int row, col;
    
        std::cout << "Введите координаты для открытия ячейки (строка и столбец): ";
        std::cin >> row >> col;

        minesweeper.openCell(row, col);

        std::cout << "Поле после открытия ячейки:" << std::endl;
        minesweeper.printBoard(true); // Показываем мины после открытия
    }
    return 0;
}
