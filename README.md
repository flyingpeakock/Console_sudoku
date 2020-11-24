# Console Sudoku

Simple ncurses program to play sudoku in the terminal
written entirely in C++

## How to Play
Fill in all the missing squares with no repeating digits in
the column, row or box.
Use hjkl to navigate around the board.
Press i or p to enter input mode or pencil mode respectively.
This game supports up to 3 pencil marks per box.
Wrong inputs are marked in red if your terminal supports it.
To remove a wrong input or the most recent pencil mark press
your spacebar in their respective modes.
To remove a specific pencil mark enter that number in the box
when in pencil mode.

## How to Install
clone this repository then compile using g++     
ex: g++ -O3 \*.cpp -lncurses -o console_sudoku   
-lncurses flag is required to link ncurses.h   
-O3 is recommended to speed up puzzle generation but is not required.

## Generate or Solve Sudoku Puzzles
You can use the Generator files and Solver files to generate
or solve sudoku puzzles, some C++ experience is recommended
but not required if you don't mind learning a little.

To solve an array create a Solver object and pass the 
unsolved puzzle to the constructor. The unsolved puzzle
can be an int\*\*, int[9][9] or a 9x9 std::array. Solve the 
puzzle by calling the solve method on the Solver object.
To get the solved puzzle call the getGrid method on the object,
this method returns a 9x9 std::array. 
To check if the supplied puzzle generates a unique solution 
the method isUnique may be called, this returns a boolean.

The generator uses Solver to build and check uniqueness of puzzles,
To create a puzzle create a Generator object. To get the unsolved
puzzle call the method getGrid. To get the solved puzzle call the
method getSolution.

