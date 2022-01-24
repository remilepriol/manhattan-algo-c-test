#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "checksolution.h"


void test(Constraints constraints){
    int trySolution[4][4]={
        {1,2,3,4},
        {4,3,2,1},
        {2,1,4,3},
        {3,4,1,2}
    };

    // print_grid(constraints, trySolution);
    if (isSudoku(trySolution)!=1){
        printf("Error: isSudoku returns %d instead of 1\n", isSudoku(trySolution));
    }
    if (isSolution(constraints, trySolution)!=0){
        printf("Error: isSolution returns %d instead of 0\n", isSolution(constraints, trySolution));
    }
    Constraints visibles = countVisibles(trySolution);
    if (isSolution(visibles, trySolution) != 1){
        printf("Error: isSolution returns %d instead of 1\n", isSolution(visibles, trySolution));
    }

    trySolution[0][0] = 2;
    if (isSudoku(trySolution)!=0){
        printf("Error: isSudoku returns %d instead of 0\n", isSudoku(trySolution));
    }

}

//list all possible rows
const int SudokuVectors[24][4] = {
    {1,2,3,4},
    {1,2,4,3},
    {1,3,2,4},
    {1,3,4,2},
    {1,4,3,2},
    {1,4,2,3},
    {2,1,3,4},
    {2,1,4,3},
    {2,3,1,4},
    {2,3,4,1},
    {2,4,3,1},
    {2,4,1,3},
    {3,1,2,4},
    {3,1,4,2},
    {3,2,1,4},
    {3,2,4,1},
    {3,4,2,1},
    {3,4,1,2},
    {4,1,3,2},
    {4,1,2,3},
    {4,3,1,2},
    {4,3,2,1},
    {4,2,3,1},
    {4,2,1,3},
};
// possible pairs of constraints (unordered)
const int ConstraintPairs[5][2]= {
    {1,2},{1,3},{1,4},{2,2},{2,3}
};


int main(int argc, char **argv){
    // open and read problem file
    char* filename = argv[1];
    Constraints constraints = read_constraints(filename);
    test(constraints);

    // Fist generate a dictionary returning possible vectors for each constraint
    // printf("Possible pairs of constraint-vector\n");
    int possibleRowCount[4][4] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int possibleRows[4][4][6][4];
    int visibleLeft;
    int visibleRight;
    int max;
    // iterate over all sudoku rows
    for(int j=0;j<24;j++){
        // check constraint value
        visibleLeft = 0;
        max = 0;
        for(int k=0;k<4;k++){
            if (SudokuVectors[j][k]>max){
                max = SudokuVectors[j][k];
                visibleLeft++;
            }
        }
        visibleRight = 0;
        max = 0;
        for(int k=0;k<4;k++){
            if (SudokuVectors[j][3-k]>max){
                max = SudokuVectors[j][3-k];
                visibleRight++;
            }
        }
        for(int k=0;k<4;k++){
            possibleRows[visibleLeft-1][visibleRight-1][possibleRowCount[visibleLeft-1][visibleRight-1]][k] = SudokuVectors[j][k];
        }
        possibleRowCount[visibleLeft-1][visibleRight-1] ++;
        // print row and visbile count
        /* printf("%d| %d %d %d %d |%d\n",
            visibleLeft,
            SudokuVectors[j][0],
            SudokuVectors[j][1],
            SudokuVectors[j][2],
            SudokuVectors[j][3],
            visibleRight
        ); */
    }

    int solution[4][4] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
    // Then for each row, iterate over possible SudokuVectors
    // in a depth first search
    // and check for sudoku satisfaction to remove branches
    bool sudokuCol, constraintsCol;
    for (int i1 =0; i1<possibleRowCount[constraints.west[0]-1][constraints.east[0]-1];i1++){
        for (int k=0;k<4;k++){
            solution[0][k] = possibleRows[constraints.west[0]-1] [constraints.east[0]-1][i1][k];
        }
        for (int i2 =0; i2<possibleRowCount[constraints.west[1]-1][constraints.east[1]-1];i2++){
            sudokuCol=true;
            for (int k=0;k<4;k++){
                solution[1][k] = possibleRows[constraints.west[1]-1] [constraints.east[1]-1][i2][k];
                if (solution[1][k]==solution[0][k]){
                    sudokuCol=false;
                }
            }
            if(!sudokuCol){
                continue;
            }

            for (int i3 =0; i3<possibleRowCount[constraints.west[2]-1][constraints.east[2]-1];i3++){
                sudokuCol = true;
                for (int k=0;k<4;k++){
                    solution[2][k] = possibleRows[constraints.west[2]-1] [constraints.east[2]-1][i3][k];
                    if (solution[2][k]==solution[1][k]
                        || solution[2][k]==solution[0][k]){
                        sudokuCol=false;
                    }
                }
                if(!sudokuCol){
                    continue;
                }

                for (int i4 =0; i4<possibleRowCount[constraints.west[3]-1][constraints.east[3]-1];i4++){
                    sudokuCol = true;
                    for (int k=0;k<4;k++){
                        solution[3][k] = possibleRows[constraints.west[3]-1] [constraints.east[3]-1][i4][k];
                        if (solution[3][k]==solution[0][k]
                            ||solution[3][k]==solution[1][k]
                            ||solution[3][k]==solution[2][k]){
                            sudokuCol=false;
                        }
                    }

                    if (sudokuCol&checkColConstraints(constraints, solution)){
                        print_grid(constraints, solution);
                    }
                }
            }
        }
    }

    return 0;
}