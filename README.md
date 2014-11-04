Sudoku puzzle solver
============

The Sudoku puzzle solver aims to solving 9x9 [*Sudoku puzzles*](http://www.sudoku.name/rules/en). It reads puzzle from a **CSV file**, with 0's representing blanks. The solver solves puzzle using **recursive backtracking** algorithm. The solution can be saved to a CSV file.

The code was written in **C++** using **Qt Creator** for cross-platform use. SudokuSolver.app running on Mac OS X and SudokuSolver.exe running on Windows were uploaded. 

<h3>How to use
----------------------
**1. Load a .csv file.**

![](/images/openFile.png)

**2. Error message pop up if the input is not a validate Sudoku puzzle.**

![](/images/error1.png) 
![](/images/error2.png) 
![](/images/error3.png)

**3. Click the 'Solve puzzle' button.**

![](/images/solve puzzle.png)

**4. Solution shows in the bottom table.**

![](/images/Solution.png)

**5. Save solution to a .csv file.**

![](images/saveSolution.png)

