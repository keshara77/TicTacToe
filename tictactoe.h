#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function Declarations
char** initBoard(int n);
void displayBoard(char** board, int n);
int isValidMove(char** board, int n, int row, int col);
void getUserMove(int* row, int* col, int n, char player);
void computerMove(char** board, int n, int* row, int* col);
int checkWinner(char** board, int n, char player);
int checkDraw(char** board, int n);
void logMove(FILE* logFile, int playerIndex, char player, int row, int col);

#endif

