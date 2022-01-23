#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int isSudoku(int solution[4][4]){
    // check if the index - 1 is present in a row or in a column
    int isPresentRow[4];
    int isPresentCol[4];

    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            isPresentRow[j] = 0;
            isPresentCol[j] = 0;
        }
        for (int j=0;j<4;j++){
            isPresentRow[solution[i][j]-1] = 1;
            isPresentCol[solution[j][i]-1] = 1;
        }
        for (int j=0;j<4;j++){
            if(isPresentRow[j]==0 || isPresentCol[j]==0){
                return 0;
            }
        }
    }
    return 1;
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

int areConstraintsEqual(Constraints c1, Constraints c2){
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

int isSolution(Constraints constraints, int solution[4][4]){
    Constraints visibles = countVisibles(solution);
    return areConstraintsEqual(constraints, visibles) && isSudoku(solution);
}
