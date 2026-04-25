#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int loop_it_back(int current){
    if (current > 99){
        while (current > 99){
            current -= 100;
        }
    }else if (current < 0){
        while (current < 0){
            current += 100;
        }
    }
    return current;
    
}

int main(int argc, char* argv[]){

    if (argc != 2){
        fprintf(stderr, "Bad usage, require FILE\n. For this puzzle you need your own input.");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");

    if (!input){
        fprintf(stderr, "Unable to open file %s:", argv[1]);
        perror("");
        fprintf(stderr, "\n");
        return 1;
    }


    int current = 50;
    int number_of_zeros = 0;
    while (true){
        char direction = 'A';
        int amount = 0;
        int res = fscanf(input, "%c%d\n", &direction, &amount);
        if (res == EOF){
            break;
        }
        /*
        Directly using % give weird behavior, so we use a custom solution
        */
        switch (direction)
        {
        case 'R':
            current += amount;
            current = loop_it_back(current);

            break;
        case 'L':
            current -= amount;
            current = loop_it_back(current);

            break;
        default:
            fprintf(stderr, "Unknown direction: %c", direction);
            return 1;
            break;
        }

        if (current == 0){
            number_of_zeros += 1;
        } 
        
    }
    printf("answer: %d\n", number_of_zeros);

    fclose(input);
    return 0;
}