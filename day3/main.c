#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

#define MAX_LENGHT 256

int joltage_in_bank(const char* line){
    size_t lenght = strlen(line)-1; // we remove the '\n'

    int first_maximum = -1;
    size_t first_maximum_index = -1;
    int second_maximum = -1;
    size_t second_maximum_index = -1;

    size_t second_search_starting_index = -1;

    for (size_t i=0; i<lenght; i++){
        int current = line[i] - '0';
        if (current > first_maximum){
            first_maximum = current;
            first_maximum_index = i;
        }
    }
    second_search_starting_index = first_maximum_index;
    // if the first maximum is the last number, then we redo the search from the beginning
    if (first_maximum_index == lenght-1) second_search_starting_index = 0; 
    
    for (size_t i=second_search_starting_index; i<lenght; i++){
        int current = line[i] - '0';
        if (current > second_maximum && first_maximum_index != i /*&& current != first_maximum*/){
            second_maximum = current;
            second_maximum_index = i;
        }
    }


    int tmp = -1;
    if (second_maximum_index < first_maximum_index){
        tmp = second_maximum;
        second_maximum = first_maximum;
        first_maximum = tmp;
    }
    if (second_maximum == -1){
        printf(" ");
    }
    //printf("first maximum is %d at %ld\nsecond maximum is %d at %ld\n\n", first_maximum, first_maximum_index, second_maximum, second_maximum_index);
    printf("%d%d\n", first_maximum, second_maximum);
    return first_maximum*10+second_maximum;
}



int main(int argc, char* argv[]){
    if (argc != 2){
        fprintf(stderr, "Not enought argument, excepted FILE\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");

    char line[MAX_LENGHT] = {0};

    if (!input){
        fprintf(stderr, "Couldn't open file '%s': %s\n", argv[1], strerror(errno));
        return 1;
    }

    int sum = 0;
    while (fgets(line, MAX_LENGHT, input)){
        sum +=  joltage_in_bank(line);
    }

    printf("final sum: %d\n", sum);

    fclose(input);
    return 0;
}