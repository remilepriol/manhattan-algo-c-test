#ifndef CHECKSOLUTION_H
#define CHECKSOLUTION_H

#include "util.h"

int isSudoku(int solution[4][4]);

Constraints countVisibles(int solution[4][4]);

int areConstraintsEqual(Constraints c1, Constraints c2);

int isSolution(Constraints constraints, int solution[4][4]);


#endif