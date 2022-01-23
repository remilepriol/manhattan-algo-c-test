#ifndef UTIL_H
#define UTIL_H

typedef struct Constraints{
    int north[4];
    int south[4];
    int east[4];
    int west[4];
} Constraints;

Constraints read_constraints(char* filename);

void print_grid(Constraints constraints, int solution[4][4]);

#endif