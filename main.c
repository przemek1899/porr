#include "matrixGenerator.h"
#include <stdio.h>
#include <time.h>

int main(){

    printf("projekt PORR\n");
    generateRandomMatrix();

    clock_t start_t, end_t, total_t;

    start_t = clock();

    //tu jest miejsce na Twój kod

    end_t = clock();
    total_t = (double) (start_t - end_t) / CLOCKS_PER_SEC;

    return 0;
}
