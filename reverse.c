/* 22.6.2025, Valtteri Ahola, Project 1: Warmup to C and Unix programming */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *line;            
    struct Node *next;
} NODE;

void writeReverse(NODE *node, FILE *file);

int main(int argc, char *argv[]) {
    FILE *tiedosto;
    //char aRivi[60];
    char *buffer = NULL;
    size_t bufsize = 0;
    size_t aLine;

    
    NODE *pStart = NULL, *pEnd = NULL;
    NODE *pNew, *ptr;

    if (argc == 2) {
        // Read from file and print to console
        if((tiedosto = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "Cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        while ((aLine = getline(&buffer, &bufsize, tiedosto)) != -1) {
            printf("%s", buffer);
        }
        if (buffer != NULL) {
            free(buffer);
        }
        fclose(tiedosto);
    } 
    else if (argc == 1) {
        // Read from stdin
        if ((aLine = getline(&buffer, &bufsize, stdin)) != -1) {
            printf("%s", buffer);
        }

        if (buffer != NULL) {
            free(buffer);
        }
    } 
    else if (argc == 3) {
        // input file and output file are the same
        if(strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        // Read from input file and write to output file
        if((tiedosto = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "Cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        
        // Read lines into linked list
        while ((aLine = getline(&buffer, &bufsize, tiedosto)) != -1) {
            if ((pNew = (NODE*)malloc(sizeof(NODE))) == NULL) {
                fprintf(stderr, "Malloc failed\n");
                exit(1);
            }
            
            // Allocate memory and copy the line
            pNew->line = strdup(buffer);
            if (pNew->line == NULL) {
                fprintf(stderr, "String duplication failed\n");
                free(pNew);
                exit(1);
            }
            
            pNew->next = NULL;
            
            if(pStart == NULL) {  
                pStart = pNew;
                pEnd = pNew;
            } else {
                pEnd->next = pNew;
                pEnd = pNew;
            }
        }
        fclose(tiedosto);
    
        // Write to output file
        if((tiedosto = fopen(argv[2], "w")) == NULL) {
            fprintf(stderr, "Cannot open file '%s'\n", argv[2]);
            exit(1);
        }

        writeReverse(pStart, tiedosto);

        fclose(tiedosto);

        // Memory release
        ptr = pStart;
        while (ptr != NULL) {
            pStart = ptr->next;
            free(ptr->line);  // Free the string memory
            free(ptr);
            ptr = pStart;
        }
    }
    else {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        exit(1);
    }

    return 0;
}

void writeReverse(NODE *node, FILE *file) {
    if (node == NULL) return;
    writeReverse(node->next, file);

    size_t len = strlen(node->line);
    if (len > 0 && node->line[len-1] == '\n') {
        node->line[len-1] = '\0';  // Remove the newline
    }

    fprintf(file, "%s\n", node->line);
}