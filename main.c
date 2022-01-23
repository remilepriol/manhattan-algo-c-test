#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "checksolution.h"

int main() {
    // open and read problem file
    char* filename = "/Users/lepriolr/Drive/professionnel/fotonower/algo-c/test_remi.txt";
    Constraints constraints = read_constraints(filename);
    int solution[4][4]={
        {1,2,3,4},
        {4,3,2,1},
        {2,1,4,3},
        {3,4,1,2}
    };

    print_grid(constraints, solution);
    printf("Is sudoku ? %d\n", isSudoku(solution));
    printf("Is solution ? %d\n", isSolution(constraints, solution));

    Constraints visibles = countVisibles(solution);
    print_grid(visibles, solution);
    printf("Is solution ? %d\n", isSolution(visibles, solution));

    solution[0][0] = 2;
    print_grid(constraints, solution);
    printf("is sudoku ? %d\n", isSudoku(solution));

    return 0;
}