#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"

bool isSudokuCol(int solution[4][4]){
    // check if each number appears no more than once in each column
    int isPresent[5];
    for (int i=0;i<4;i++){
        for (int j=0;j<5;j++){
            isPresent[j] = 0;
        }
        for (int j=0;j<4;j++){
            isPresent[solution[j][i]] += 1;
        }
        for (int j=1;j<5;j++){
            // check if some number in 1,2,3,4 appears more than once
            if(isPresent[j]>1){
                return 0;
            }
        }
    }
    return 1;
}

bool isSudokuRow(int solution[4][4]){
    // check if the index is present in a row
    int isPresent[5];
    for (int i=0;i<4;i++){
        for (int j=0;j<5;j++){
            isPresent[j] = 0;
        }
        for (int j=0;j<4;j++){
            isPresent[solution[i][j]] += 1;
        }
        for (int j=1;j<5;j++){
            // check if some number in 1,2,3,4 appears more than once
            if(isPresent[j]>1){
                return 0;
            }
        }
    }
    return 1;
}

bool isSudoku(int solution[4][4]){
    return isSudokuRow(solution) && isSudokuCol(solution);
}

Constraints countVisibles(int solution[4][4]){
    Constraints visibles;
    int count;
    int max;
    for (int i=0;i<4;i++){
        count = 0;
        max = 0;
        for (int j=0;j<4;j++){
            if (solution[i][j]>max){
                max = solution[i][j];
                count++;
            }
        }
        visibles.west[i] = count;

        count = 0;
        max = 0;
        for (int j=0;j<4;j++){
            if (solution[i][3-j]>max){
                max = solution[i][3-j];
                count++;
            }
        }
        visibles.east[i] = count;

        count = 0;
        max = 0;
        for (int j=0;j<4;j++){
            if (solution[j][i]>max){
                max = solution[j][i];
                count++;
            }
        }
        visibles.north[i] = count;

        count = 0;
        max = 0;
        for (int j=0;j<4;j++){
            if (solution[3-j][i]>max){
                max = solution[3-j][i];
                count++;
            }
        }
        visibles.south[i] = count;
    }
    return visibles;
}

bool areConstraintsEqual(Constraints c1, Constraints c2){
    for (int i=0;i<4;i++){
        if (
            c1.north[i]!=c2.north[i]
            || c1.south[i]!=c2.south[i]
            || c1.east[i]!=c2.east[i]
            || c1.west[i]!=c2.west[i]
        ){
            return 0;
        }
    }
    return 1;
}

bool isSolution(Constraints constraints, int solution[4][4]){
    Constraints visibles = countVisibles(solution);
    return areConstraintsEqual(constraints, visibles) && isSudoku(solution);
}
