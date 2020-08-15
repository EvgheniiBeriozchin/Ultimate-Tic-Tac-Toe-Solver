# Ultimate-Tic-Tac-Toe-Solver

## Description

This project aims to create an Ultimate Tic-Tac-Toe solver.

## Prerequisites
For the no_database version of the project, no prerequisites besides cmake and make exist.

## Run

An already built version exists in the build folder. To run, execute: ```./solver``` in the build folder.  
If you modified the code, do the following in the base directory of the project:
```
rm -r build
mkdir build
cd build
cmake ..
make
```
Then you can run ```./solver``` as with the prebuilt version.
NOTE: You are required to do the steps above when modifying the code only the first time you do so. Every next time you modify the code only ```make``` should be executed. 

You can either input a board yourself and see the result, or run a testing session. 
If you input a board, the following format is required:  
* For each subboard:  
    value: 0 - not decided, 1 - player 0 (crosses) won, 2 - player 1 (circles) won.  
    if value is 0 -> board representation without spaces, from the upper-left field to the bottom-right. 0 - empty, 1 - cross, 2 - circle.
* the subfield where the previous move was made, counted in the order above, from 0 to 8.
* the total number of tokens currently set. Used only for ordering in the transposition table and there it is, in principle, relative. So this number doesn't need to be accurate/exact.

To specify runtime behaviour, add some of the flags described below.
Examples:
* Input a board: run - ```./solver --input 2 --abp --maxp```, place the input - ```2 1 2 0 012201210 0 100200100 1 0 012012200 2 1 2 3 48```.
* Run a testing session: - ```./solver --size 50 --percentage 0.2 --seed -1 --maxp --abp --tttype 2 --ttsize 20000000 --ordering 1 --time 5 --testid "example" ```

## Flags
All flags need to have "--" before them. 
* input: 0 - run testing session, 1 - run the algorithm on an input board, insert the subboards one by one, 2 - run the algorithm on an input board, insert all the subboards at once. If you input a board for the first time, try input=1 to understand the input format. Default: 0
* size - number of boards generated for each iteration of a testing session Default: 500
* percentage - stop threshold, percentage of failed boards in an iteration in order to stop the program. Default: 0.05
* seed - seed for randomization of generated boads. -1 - random seed (based on time), any other value will be made the seed for the run. Default: 958654 (random fixed number)
* time - time limit for running the algorithm for one board IN MINUTES (integer). Default: 5
* maxp - enable maximum value pruning Default: disabled
* abp - enable alpha-beta pruning Default: disabled
* evaluation - the value to which a full subboard is evaluated Default: 0, i.e. ternary evaluation. For binary evaluation set this flag to -1/1.
* tttype - transposition table type: 0 - none, 1 - latest boards, 2 - most complex boards, 3 - both. Default: 0
* ttsize - size of transposition table. Default: 2000000
* ordering - move ordering: 0 - default ordering (row by row from upper-left to bottom-right), 1 - move ordering 2, 2 - move ordering 3.
* testid - a string for querying the testing results in the database afterwards.
