#include <stdio.h>
#include <stdlib.h>
#include "util.h"


#ifndef MAX_BUF
#define MAX_BUF 256
#endif


Constraints read_constraints(char* filename){
    FILE*  fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
    }

    Constraints constraints;
    // read one line at a time and store them in constraints
    char buffer[MAX_BUF];
    while (fgets(buffer, MAX_BUF, fp)){
        printf("%s", buffer);
        if (buffer[0]=='N'){
            for (int i=0; i<4; i++){
                constraints.north[i] = (int) buffer[(i+1)*2] - '0';
            }
        }
        if (buffer[0]=='S'){
            for (int i=0; i<4; i++){
                constraints.south[i] = (int) buffer[(i+1)*2] - '0';
            }
        }
        if (buffer[0]=='O'){
            for (int i=0; i<4; i++){
                constraints.west[i] = (int) buffer[(i+1)*2] - '0';
            }
        }
        if (buffer[0]=='E'){
            for (int i=0; i<4; i++){
                constraints.east[i] = (int) buffer[(i+1)*2] - '0';
            }
        }
    };

    fclose(fp);
    return constraints;
};


void print_grid(Constraints constraints){
    printf("\n | ");
    for(int i=0; i < 4; i++){
        printf("%d ", constraints.north[i]);
    }
    printf("| \n");
    printf("-+---------+-\n");
    for (int i=0; i < 4; i++){
        printf("%d|         |", constraints.west[i]);
        printf("%d\n", constraints.east[i]);
    }
    printf("-+---------+-\n | ");
    for(int i=0; i < 4; i++){
        printf("%d ", constraints.south[i]);
    }
    printf("| \n\n");
};