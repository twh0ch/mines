#include "minesweeper.hpp"

int main() {
    
    int rows, cols, numberOfMines;
    
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
        minesweeper.printBoard(true);
    }
    return 0;
}