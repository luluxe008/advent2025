
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

typedef struct Grid{
    char** inner;
    int height;
    int width;
} Grid;

Grid fill_grid_from_file(FILE* input, int height, int width){
    Grid grid = {
        NULL,
        height,
        width
    };
    grid.inner = malloc(height*sizeof(char*));
    for (int i=0; i<height; i++){
        grid.inner[i] = malloc(sizeof(char)*width);
    }

    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            char current = fgetc(input);
            if (current == '\n'){
                current = fgetc(input);
            }
            grid.inner[i][j] = current;
        }
    }
    return grid;
}

char get_cell(Grid* grid, int row, int coloumn){
    if (row < 0 || coloumn < 0 || row >= grid->height || coloumn >= grid->width){
        return ' ';
    }
    return grid->inner[row][coloumn];
}

void print_neighbors(char neighbors[8]){
    printf("%c %c %c\n%c X %c\n%c %c %c", neighbors[0], neighbors[1], neighbors[2], neighbors[3], neighbors[4], neighbors[5], neighbors[6], neighbors[7]);
}

void get_neighbors_around_cell(Grid* grid, int row, int coloumn, char* neighbors){
    /*
    0 1 2
    3   4
    5 6 7
    */
    
    neighbors[0] = get_cell(grid, row-1, coloumn-1);
    neighbors[1] = get_cell(grid, row-1, coloumn);
    neighbors[2] = get_cell(grid, row-1, coloumn+1);
    neighbors[3] = get_cell(grid, row, coloumn-1);
    neighbors[4] = get_cell(grid, row, coloumn+1);
    neighbors[5] = get_cell(grid, row+1, coloumn-1);
    neighbors[6] = get_cell(grid, row+1, coloumn);
    neighbors[7] = get_cell(grid, row+1, coloumn+1);

}

int count_roll_in_neighbors(char neighbors[8]){
    int count = 0;
    for (int i=0; i<8; i++){
        if (neighbors[i] == '@'){
            count++;
        }
    }
    return count;
}

void free_grid(Grid* grid){
    //valgrind:
    //"All heap blocks were freed -- no leaks are possible"
    // aura farm +10000000 aura
    for (int i=0; i<grid->height; i++){
        free(grid->inner[i]);
    }
    free(grid->inner);
}

void print_line(const char* str, int width){
    char* tmp = malloc(width+1);
    tmp[width] = '\0';
    strncpy(tmp, str, width);
    printf("%s", tmp);
    free(tmp);
}



int main(int argc, char* argv[]){
    if (argc != 2){
        fprintf(stderr, "Excepted FILE\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input){
        fprintf(stderr, "Unable to open file: %s", strerror(errno));
        return 1;
    }
    //first we count number of line and their witdh;
    int line = 1;

    char c;
    for (c = fgetc(input); c !=EOF; c = fgetc(input)){
        if (c=='\n') line++;
    }
    fseek(input, 0, SEEK_SET);

    //then the lenght of one line

    int width = 0;
    for (c = fgetc(input); c!='\n'; c=fgetc(input)) width++;

    printf("lines: %d\n", line);
    printf("width: %d\n", width);

    fseek(input, 0, SEEK_SET);

    Grid grid = fill_grid_from_file(input, line, width);
    
    
    int accesibles = 0;
    for (int i=0; i<grid.height; i++){
        for (int j=0; j<grid.width; j++){
            if (get_cell(&grid, i, j) != '@') continue;
            char neighbors[8] = {};
            get_neighbors_around_cell(&grid, i, j, neighbors);
            //print_neighbors(neighbors);
            int count = count_roll_in_neighbors(neighbors);
            if (count < 4){
                printf("X");
                accesibles++;
            }else{
                printf("%c", get_cell(&grid, i, j));
            }
        }
        printf("\n");
    }

    printf("accessible: %d", accesibles);

    // good citizen duty
    free_grid(&grid); 
    fclose(input);
    return 0;
}