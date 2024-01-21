#include <iostream>
#include <vector>
#include <random>

class Minesweeper {
public:
    Minesweeper(int rows, int cols, int numberOfMines);

    void printBoard(bool showMines = false) const;

    void openCell(int row, int col);

private:
    enum class Cell { Closed, Open, Flag };

    int rows;
    int cols;
    double minePercentage;
    std::vector<std::vector<Cell> > board;
    std::vector<std::vector<int> > mines;

    int numberOfMines;

    void generateMines();

    void calculateNumbers();
};
