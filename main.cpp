#include "SudokuSolver.h"

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    SudokuSolver solver;

    string filename;

    cout << "=========================================\n";
    cout << "         Sudoku Solver (C++)\n";
    cout << "=========================================\n\n";

    cout << "Enter puzzle file path: ";
    cin >> filename;

    if (!solver.loadPuzzle(filename))
    {
        cout << "\nFailed to load puzzle.\n";
        return 1;
    }

    cout << "\nOriginal Puzzle\n";
    cout << "-------------------------\n";
    solver.printBoard();

    if (!solver.validatePuzzle())
    {
        cout << "The puzzle is invalid.\n";
        return 1;
    }

    auto start = high_resolution_clock::now();

    bool solved = solver.solve();

    auto stop = high_resolution_clock::now();

    auto duration =
        duration_cast<microseconds>(stop - start);

    if (solved)
    {
        cout << "\nSolved Puzzle\n";
        cout << "-------------------------\n";

        solver.printBoard();

        cout << "Statistics\n";
        cout << "-------------------------\n";
        cout << "Recursive Calls : "
             << solver.getRecursiveCalls()
             << endl;

        cout << "Backtracks      : "
             << solver.getBacktracks()
             << endl;

        cout << "Execution Time  : "
             << duration.count()
             << " microseconds\n";

        char choice;

        cout << "\nSave solved puzzle? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            string outputFile;

            cout << "Output filename: ";
            cin >> outputFile;

            if (solver.savePuzzle(outputFile))
            {
                cout << "Puzzle saved successfully.\n";
            }
            else
            {
                cout << "Unable to save file.\n";
            }
        }
    }
    else
    {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}