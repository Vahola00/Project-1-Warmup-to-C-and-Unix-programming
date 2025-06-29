/* 23.6.2025, Valtteri Ahola, Project 2: Unix Utilities - my-unzip.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int i;
    int32_t a;
    char b;
    FILE *tiedosto;


    if(argc == 1) {
        printf("my-unzip: file1 [file2...]\n");
        exit(0);
    } else {
        for (i = 1; i < argc; i++) {
            // Read from compressed file and print to stdout in readable form
            if((tiedosto = fopen(argv[i], "rb")) == NULL) {
                printf("my-zip: cannot open file\n");
                exit(1);
            }
            while (fread(&a, sizeof(a), 1, tiedosto) != 0 && fread(&b, sizeof(b), 1, tiedosto) != 0) {
                printf("%d%c", a, b);
            }
            fclose(tiedosto);
            // Removes compressed file after printing
            remove(argv[i]);
        }
    }

    printf("\n");
    return 0;
}