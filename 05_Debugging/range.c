#include <stdio.h>
#include <stdlib.h>

void range(int start, int stop, int step) {
    for (int i = start; i < stop; i+=step) {
        printf("%d ", i);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    switch (argc) {
        case 1: {
            printf("Returns a list of arithmetic progressions.\n");
            printf("Syntax: range ([start, ]stop[, step])\n");
            printf("    start - An integer number. The number of the beginning of the sequence.\n");
            printf("    stop - Required. An integer number. Generates a number up to a given number, but not including it.\n");
            printf("    step - An integer number. The difference between each number from the sequence.\n");
            break;
        }
        case 2: {
            range(0, atoi(argv[1]), 1);
            break;
        }
        case 3: {
            range(atoi(argv[1]), atoi(argv[2]), 1);
            break;
        }
        case 4: {
            range(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
            break;
        }
        default:
            return 1;
    }
	return 0;
}