#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef struct RangeNode{
    long long lower;
    long long upper;
    struct RangeNode* next;
} RangeNode;

/*
Valgrind is crying over clean_list and test_number (980 errors LOL) but i can't figure it out.
At least we have no memory leaks.
*/
void clean_list(RangeNode* current){
    RangeNode* tmp;
    while (current != NULL){
        tmp = current;
        current = tmp->next;
        free(tmp);
    }
}

bool test_number(long long number, RangeNode* current){
    do{
        if (current->lower <= number && number <= current->upper){
            return true;
        }
        current = current->next;
    } while (current != NULL);
    return false;
}

int main(int argc, char** argv){
    if (argc != 2){
        fprintf(stderr, "Need input file as first argument");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");

    if (!input){
        fprintf(stderr, "Unable to open file '%s': %s\n", argv[1], strerror(errno));
        return 1;
    }
    char line[250] = {0};
    RangeNode head = {
        0,
        0, 
        NULL,
    };
    RangeNode* current_node = &head;

    /*we first read the ranges of freshness */
    char* res = fgets(line, 250, input);

    do{
        if (res == NULL){
            fprintf(stderr, "Unexepcted EOF\n");
        }
        long long a, b;
        sscanf(line, "%lld-%lld", &a, &b);

        current_node->next = malloc(sizeof(RangeNode));
        if (current_node->next == NULL){
            fprintf(stderr, "malloc failed\n");
            return 1;
        }
        current_node->lower = a;
        current_node->upper = b;
        
        current_node = current_node->next;

        res = fgets(line, 250, input);
        if (res == NULL){
            fprintf(stderr, "fgets failed");
            return 1;
        }
    } while (line[0] != '\n');

    int fresh_number = 0;

    while (!feof(input)){
        long long number = 0;
        fscanf(input, "%lld\n", &number);
        bool test = test_number(number, &head);
        if (test) fresh_number += 1;
    }

    clean_list(head.next);
    fclose(input);
    printf("fresh number: %d", fresh_number);
    return 0;
}