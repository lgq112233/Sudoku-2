#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

extern int Board[25][9][9];
extern int Try_List[9];
extern int read(char str[]);
extern int Judge(int s, int x, int y, int num);
extern int Fill_Sudoku(int s, int x, int y);
extern int Solve_Sudoku(char File[]);
extern int Creat_Sudoku(int Sodoku_Num);
extern int Random_Init(int Num[]);