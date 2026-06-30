#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <vector>
#include <string>

class SudokuSolver
{
private:
    std::vector<std::vector<int>> board;

    long long recursiveCalls;
    long long backtracks;

    bool solveHelper();

    bool isSafe(int row, int col, int num);

    bool findEmptyCell(int &row, int &col);

    bool isRowValid(int row);

    bool isColumnValid(int col);

    bool isBoxValid(int startRow, int startCol);

public:
    SudokuSolver();

    bool loadPuzzle(const std::string &filename);

    bool savePuzzle(const std::string &filename);

    void printBoard() const;

    bool validatePuzzle();

    bool solve();

    long long getRecursiveCalls() const;

    long long getBacktracks() const;

    void resetStatistics();
};

#endif