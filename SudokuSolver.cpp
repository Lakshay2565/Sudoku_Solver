#include "SudokuSolver.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_set>

using namespace std;

//--------------------------------------------------
// Constructor
//--------------------------------------------------

SudokuSolver::SudokuSolver()
{
    board.assign(9, vector<int>(9, 0));
    recursiveCalls = 0;
    backtracks = 0;
}

//--------------------------------------------------
// Reset statistics
//--------------------------------------------------

void SudokuSolver::resetStatistics()
{
    recursiveCalls = 0;
    backtracks = 0;
}

//--------------------------------------------------
// Getters
//--------------------------------------------------

long long SudokuSolver::getRecursiveCalls() const
{
    return recursiveCalls;
}

long long SudokuSolver::getBacktracks() const
{
    return backtracks;
}

//--------------------------------------------------
// Load puzzle from text file
//--------------------------------------------------

bool SudokuSolver::loadPuzzle(const string &filename)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cout << "Error opening file.\n";
        return false;
    }

    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (!(inputFile >> board[row][col]))
            {
                cout << "Invalid puzzle format.\n";
                return false;
            }

            if (board[row][col] < 0 || board[row][col] > 9)
            {
                cout << "Puzzle contains invalid values.\n";
                return false;
            }
        }
    }

    inputFile.close();

    return true;
}

//--------------------------------------------------
// Save solved puzzle
//--------------------------------------------------

bool SudokuSolver::savePuzzle(const string &filename)
{
    ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        return false;
    }

    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            outputFile << board[row][col] << " ";
        }

        outputFile << endl;
    }

    outputFile.close();

    return true;
}

//--------------------------------------------------
// Print puzzle
//--------------------------------------------------

void SudokuSolver::printBoard() const
{
    cout << "\n";

    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            cout << "------+-------+------\n";
        }

        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0 && col != 0)
            {
                cout << "| ";
            }

            cout << board[row][col] << " ";
        }

        cout << endl;
    }

    cout << endl;
}

//--------------------------------------------------
// Row validation
//--------------------------------------------------

bool SudokuSolver::isRowValid(int row)
{
    unordered_set<int> used;

    for (int col = 0; col < 9; col++)
    {
        int value = board[row][col];

        if (value == 0)
            continue;

        if (used.count(value))
            return false;

        used.insert(value);
    }

    return true;
}

//--------------------------------------------------
// Column validation
//--------------------------------------------------

bool SudokuSolver::isColumnValid(int col)
{
    unordered_set<int> used;

    for (int row = 0; row < 9; row++)
    {
        int value = board[row][col];

        if (value == 0)
            continue;

        if (used.count(value))
            return false;

        used.insert(value);
    }

    return true;
}

//--------------------------------------------------
// 3x3 Box validation
//--------------------------------------------------

bool SudokuSolver::isBoxValid(int startRow, int startCol)
{
    unordered_set<int> used;

    for (int row = startRow; row < startRow + 3; row++)
    {
        for (int col = startCol; col < startCol + 3; col++)
        {
            int value = board[row][col];

            if (value == 0)
                continue;

            if (used.count(value))
                return false;

            used.insert(value);
        }
    }

    return true;
}

//--------------------------------------------------
// Validate entire puzzle
//--------------------------------------------------

bool SudokuSolver::validatePuzzle()
{
    for (int row = 0; row < 9; row++)
    {
        if (!isRowValid(row))
            return false;
    }

    for (int col = 0; col < 9; col++)
    {
        if (!isColumnValid(col))
            return false;
    }

    for (int row = 0; row < 9; row += 3)
    {
        for (int col = 0; col < 9; col += 3)
        {
            if (!isBoxValid(row, col))
                return false;
        }
    }

    return true;
}
//--------------------------------------------------
// Find the next empty cell
//--------------------------------------------------

bool SudokuSolver::findEmptyCell(int &row, int &col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (board[row][col] == 0)
            {
                return true;
            }
        }
    }

    return false;
}

//--------------------------------------------------
// Check if a number can be placed
//--------------------------------------------------

bool SudokuSolver::isSafe(int row, int col, int num)
{
    // Check row
    for (int i = 0; i < 9; i++)
    {
        if (board[row][i] == num)
            return false;
    }

    // Check column
    for (int i = 0; i < 9; i++)
    {
        if (board[i][col] == num)
            return false;
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startCol; j < startCol + 3; j++)
        {
            if (board[i][j] == num)
                return false;
        }
    }

    return true;
}

//--------------------------------------------------
// Recursive Backtracking Solver
//--------------------------------------------------

bool SudokuSolver::solveHelper()
{
    recursiveCalls++;

    int row;
    int col;

    // Puzzle solved
    if (!findEmptyCell(row, col))
    {
        return true;
    }

    // Try every number
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(row, col, num))
        {
            board[row][col] = num;

            if (solveHelper())
            {
                return true;
            }

            // Undo choice
            board[row][col] = 0;
            backtracks++;
        }
    }

    return false;
}

//--------------------------------------------------
// Public solve function
//--------------------------------------------------

bool SudokuSolver::solve()
{
    resetStatistics();

    if (!validatePuzzle())
    {
        cout << "Invalid Sudoku puzzle.\n";
        return false;
    }

    return solveHelper();
}