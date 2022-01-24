#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "checksolution.h"


void test(Constraints constraints){
    int solution[4][4]={
        {1,2,3,4},
        {4,3,2,1},
        {2,1,4,3},
        {3,4,1,2}
    };

    print_grid(constraints, solution);
    if (isSudoku(solution)!=1){
        printf("Error: isSudoku returns %d instead of 1\n", isSudoku(solution));
    }
    if (isSolution(constraints, solution)!=0){
        printf("Error: isSolution returns %d instead of 0\n", isSolution(constraints, solution));
    }
    Constraints visibles = countVisibles(solution);
    if (isSolution(visibles, solution) != 1){
        printf("Error: isSolution returns %d instead of 1\n", isSolution(visibles, solution));
    }

    solution[0][0] = 2;
    if (isSudoku(solution)!=0){
        printf("Error: isSudoku returns %d instead of 0\n", isSudoku(solution));
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


int main() {
    // open and read problem file
    char* filename = "/Users/lepriolr/Drive/professionnel/fotonower/algo-c/test_remi.txt";
    Constraints constraints = read_constraints(filename);
    test(constraints);

    printf("Possible pairs of constraint-vector\n");
    // possible pairs of constraints (unordered)
    int constraintPairs[5][2]= {
        {1,2},{1,3},{1,4},{2,2},{2,3}
    };
    int count;
    int max;
    // for each pairs of constraints, count number of solutions in this array
    int nbSolutions[4][4];
    int* constraintSolutions[4][4][6][4];
    int countSolutions;
    for (int i=1;i<5;i++){
        for (int l=1;l<5;l++){
            //for each pair iterate over all sudoku rows
            countSolutions=0;
            for(int j=0;j<24;j++){
                // check if that row is satisfying the left constraint
                count = 0;
                max = 0;
                for(int k=0;k<4;k++){
                    if (SudokuVectors[j][k]>max){
                        max = SudokuVectors[j][k];
                        count++;
                    }
                }
                if (count!=i){
                    continue;
                }
                // check if that row is satisfying the right constraint
                count = 0;
                max = 0;
                for(int k=0;k<4;k++){
                    if (SudokuVectors[j][3-k]>max){
                        max = SudokuVectors[j][3-k];
                        count++;
                    }
                }
                if (count!=l){
                    continue;
                }
                // print rows that are satisfying the pair of constraints
                printf("%d| %d %d %d %d |%d\n",
                    constraintPairs[i][0],
                    SudokuVectors[j][0],
                    SudokuVectors[j][1],
                    SudokuVectors[j][2],
                    SudokuVectors[j][3],
                    constraintPairs[i][1]
                );
                // and add them to the table of nbSolutions
                countSolutions++;
                // constraintSolutions[i][l][j][k];
            }
            nbSolutions[i-1][l-1]=countSolutions;
            if (countSolutions>0){
                printf("Constraints (%d,%d) has %d solutions.\n", i, l, countSolutions);
            }
        }
    }




    return 0;
}