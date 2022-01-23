#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main() {
    // open and read problem file
    char* filename = "/Users/lepriolr/Drive/professionnel/fotonower/algo-c/test_remi.txt";
    Constraints constraints = read_constraints(filename);
    print_grid(constraints);
    return 0;
}