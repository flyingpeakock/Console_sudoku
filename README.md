# Console Sudoku

Simple ncurses program to play sudoku in the terminal
written entirely in C++

## How to Play
Fill in all the missing squares with no repeating digits in
the column, row or box.
Use hjkl to navigate around the board.
Press i or p to enter input mode or pencil mode respectively.
You can also toggle between the two modes by pressing escape.
To go to a specific box on the board type g followed by the 
column number then the row number. For example, to go to 
column 4, row 2 type g42. Press c to check the puzzle for any wrong
inputs, mistakes turn red and correct inputs turn blue.
This game supports up to 3 pencil marks per box.
To remove a mistake or the most recent pencil mark press
your spacebar in their respective modes.
To remove a specific pencil mark enter that number in the box
when in pencil mode.

### Command line arguments
Arguments can be passed to the program when executing, the
following arguments are:    
* _nocolor_ turns off color   
* _noinstructions_ does not print the instructions to the right of the board    
* _nocoords_ does not print the coordinates around the board    
* _notitle_ does not print the title    
* _nomode_ does not print the mode the user is currently in
* _clean_ is equivalent to _noinstructions_, _nocoords_, _notitle_ and _nomode_    
* Any number can be passed as an argument to specify the number of unfilled squares

None or all of the arguments may be passed to the program.

## How to Install
clone this repository then compile using g++ or clang++    

### Linux
```
git clone https://github.com/flyingpeakock/Console_sudoku.git
cd Console_sudoku/
g++ -O3 ./src/*.cpp -lncurses -o console_sudoku
```
### OSX
```
git clone https://github.com/flyingpeakock/Console_sudoku.git
cd Console_sudoku/
clang++ -O3 -std=c++11 -stdlib=libc++ ./src/*.cpp -lncursesw -o console_sudoku
```

-lncursesw flag is required to link ncurses.h   
-O3 is recommended to speed up puzzle generation but is not required.   

To run this program from any directory move the generated
console_sudoku file to anywhere in your $PATH.
```
cp console_sudoku ~/.local/bin/console_sudoku
```

### Troubleshooting
If the compiler cannot find ncurses.h you need to make sure that ncurses is installed.
If you cannot find ncurses in your package manager it might be called something like
libcurses or curses instead. If it still doesn't work use the -lncurses flag instead
of -lncursesw when compiling.

## Screenshots
![new game](https://imgur.com/awu4dbQ.png)
![Same game with pencil marks, a couple boxes filled in and a mistake](https://imgur.com/ooYHXm0.png)
![Same game after check board has been called](https://imgur.com/vF97N1b.png)

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

