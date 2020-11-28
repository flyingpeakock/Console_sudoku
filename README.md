# Console Sudoku

Simple ncurses program to play sudoku in the terminal
written entirely in C++

## How to Play
Fill in all the missing squares with no repeating digits in
the column, row or box.
Use hjkl to navigate around the board.
Press i or p to enter input mode or pencil mode respectively.
To go to a specific box on the board type g followed by the 
column number then the row number. For example, to go to 
column 4, row 2 type g42.
This game supports up to 3 pencil marks per box.
Wrong inputs are marked in red if your terminal supports it.
To remove a wrong input or the most recent pencil mark press
your spacebar in their respective modes.
To remove a specific pencil mark enter that number in the box
when in pencil mode.

### Command line arguments
Arguments can be passed to the program when executing, the
following arguments are:    
* _nocolor_ disables red text on wrong input   
* _noinstructions_ does not print the instructions to the right of the board    
* _nocoords_ does not print the coordinates around the board    
* _notitle_ does not print the title    
* _nomode_ does not print the mode the user is currently in
* _clean_ is equivalent to _noinstructions_, _nocoords_, _notitle_ and _nomode_    
* Any number can be passed as an argument to specify the number of unknowns
None or all of the arguments may be passed to the program.

## How to Install
clone this repository then compile using g++     
```
git clone https://github.com/flyingpeakock/Console_sudoku.git
cd Console_sudoku/
g++ -O3 ./src/*.cpp -lncurses -o console_sudoku
```
-lncurses flag is required to link ncurses.h   
-O3 is recommended to speed up puzzle generation but is not required.   

To run this program from any directory move the generated
console_sudoku file to anywhere in your $PATH.
```
cp console_sudoku ~/.local/bin/console_sudoku
```

### Troubleshooting
If your console does not display the box characters but 
instead displays something like M-b\~U\~T over and over you 
can compile using -lncursesw instead.
```
g++ -O3 *.cpp -lncursesw -o console_sudoku
```

## Screenshots
![new game](https://i.imgur.com/OQ39ENC.png)
![Same game with pencil marks, a couple boxes filed in and a mistake](https://i.imgur.com/JpnAZH3.png)

## Generate or Solve Sudoku Puzzles
You can use the Generator files and Solver files to generate
or solve sudoku puzzles, some C++ experience is recommended
but not required if you don't mind learning a little.

To solve an unsolved puzzle create a Solver object and pass the 
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

