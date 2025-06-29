/* 23.6.2025, Valtteri Ahola, Project 2: Unix Utilities - my-zip.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAKSIMI 1000

int main(int argc, char *argv[]) {
    int i;
    int a;
    int32_t b = 1;
    FILE *tiedosto;
    char aRivi[MAKSIMI];

    if(argc == 1) {
        printf("my-zip: file1 [file2...]\n");
        exit(0);
    } else {
        for (i = 1; i < argc; i++) {
            // Read from file and write to stdout
            if((tiedosto = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "Cannot open file\n");
                exit(1);
            }
            while (fgets(aRivi, MAKSIMI, tiedosto) != NULL) {
                // Search similar characters in a row and writes them to stdout in a dedicated format (a 4-byte integer followed by a character)
                for (a = 0; a < strlen(aRivi); a++) {
                    if (aRivi[a] == '\n') {
                    continue;
                    }

                    if (aRivi[a] == aRivi[a + 1]) {
                        b = b + 1;
                    } else {
                        fwrite(&b, sizeof(b), 1, stdout);
                        fwrite(&aRivi[a], sizeof(aRivi[a]), 1, stdout);
                        b = 1;
                    }
                }
            }
            fclose(tiedosto);
            // Removes files which are compressed as a new file
            remove(argv[i]);
        }
    }

    return 0;
}