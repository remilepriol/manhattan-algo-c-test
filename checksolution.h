#ifndef CHECKSOLUTION_H
#define CHECKSOLUTION_H

#include <stdbool.h>
#include "util.h"

bool isSudokuRow(int solution[4][4]);
bool isSudokuCol(int solution[4][4]);
bool isSudoku(int solution[4][4]);

Constraints countVisibles(int solution[4][4]);

bool areConstraintsEqual(Constraints c1, Constraints c2);

bool isSolution(Constraints constraints, int solution[4][4]);


#endif