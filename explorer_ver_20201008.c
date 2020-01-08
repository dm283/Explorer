#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void move_name(int mv){
    switch (mv){
        case 1: printf("left\n"); break;
        case 2: printf("right\n"); break;
        case 3: printf("down\n"); break;
        case 4: printf("up\n"); break;
    }
}

int main(){
// BLOCK#1 = CREATE TERRAIN MAP=========================================================
// values: 0 = unknown area; 1 = known area; 2 = selenium; 3 = caverna; 9 = base
    int i, j;
    int matrix_tm[10][10];

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            matrix_tm[i][j] = 0;
        }
    }

    matrix_tm[0][0] = 9; // main base position
    // selenium areas
    matrix_tm[0][6] = 2; matrix_tm[1][2] = 2; matrix_tm[3][8] = 2; matrix_tm[4][0] = 2; matrix_tm[4][4] = 2; 
    matrix_tm[6][1] = 2; matrix_tm[7][7] = 2; matrix_tm[8][3] = 2; matrix_tm[9][0] = 2; matrix_tm[9][9] = 2;
    // caverna areas
    matrix_tm[1][8] = 3; matrix_tm[3][1] = 3; matrix_tm[5][6] = 3; matrix_tm[6][3] = 3;

    // ВИЗУАЛЬНОЕ ОТОБРАЖЕНИЕ КАРТЫ МЕСТНОСТИ
    system("cls");
    printf("TERRAIN MAP (0 = unknown area; 1 = known area; 2 = selenium; 3 = caverna; 9 = base):\n");
    printf("* * 0|1|2|3|4|5|6|7|8|9 * *\n");
    printf("-----+-+-+-+-+-+-+-+-+-----\n");
    for (i = 0; i < 10; i++) {
        printf("%d | ", i);
        for (j = 0; j < 10; j++) {
            printf("%d ", matrix_tm[i][j]);
        }
        printf("| %d\n", i);
    }
    printf("-----+-+-+-+-+-+-+-+-+-----\n");
    printf("* * 0|1|2|3|4|5|6|7|8|9 * *\n");

// BLOCK#2 = CREATE INITIAL ROVER POSITION MAP =========================================================
//Карта движения (10 x 10): 0 = unknown area; 1 = known area; 2 = rover current position
    int day, ii, matrix_rm[10][10], rcp[2] = {0, 0}; //initial array of rover coordinates (y, x)

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            matrix_rm[i][j] = 0; // i = row; j = column
        }
    }

    matrix_rm[rcp[0]][rcp[1]] = 2; // initial position = {0, 0}

    // ВИЗУАЛЬНОЕ ОТОБРАЖЕНИЕ ПЕРВОНАЧАЛЬНОЙ КАРТЫ ДВИЖЕНИЯ
    printf("\nROVER MOVEMENT MAP (0 = unknown area; 1 = known area; 2 = rover current position):\n");
    printf("* * 0|1|2|3|4|5|6|7|8|9 * *\n");
    printf("-----+-+-+-+-+-+-+-+-+-----\n");
    for (i = 0; i < 10; i++) {
        printf("%d | ", i);
        for (j = 0; j < 10; j++) {
            printf("%d ", matrix_rm[i][j]);
        }
        printf("| %d\n", i);
    }
    printf("-----+-+-+-+-+-+-+-+-+-----\n");
    printf("* * 0|1|2|3|4|5|6|7|8|9 * *\n");

    // Ввод пользователя для первого хода
    printf("\n[n]: ");
    scanf("%d", &ii);
    ii = day = 1;

// BLOCK#3 = CREATE VARIABLES =========================================================
int mv = 0;
int srand_arg = 1;
int nextRcp[2];
int setRcp[10][10]; // there will record all unique rover moves
i = j = 0;
for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
        setRcp[i][j] = 0; // i = row; j = column
    }
}
setRcp[0][0] = 1;

// BLOCK#4 = ACTIONS =========================================================
while (ii != 0){
    system("cls");
    printf("======== DAY: %d ============================================\n", day);
    printf("rcp = (%d, %d)\n", rcp[0], rcp[1]);

    // # определяем нахождение внутри known area
    // if (
    //     ((rcp[1] - 1) < 0 or cr[(rcp[1] - 1)][rcp[0]] == 1) 
    //     and 
    //     ((rcp[1] + 1) > 9 or cr[(rcp[1] + 1)][rcp[0]] == 1)
    //      and 
    //     ((rcp[0] - 1) < 0 or cr[(rcp[1])][(rcp[0] - 1)] == 1)
    //      and 
    //     ((rcp[0] + 1) > 9 or cr[(rcp[1])][(rcp[0] + 1)] == 1)):
        
    //     print("ROVER IN KNOWN AREA")
    //     break
    if (((rcp[0] - 1) < 0 || matrix_rm[(rcp[0] - 1)][rcp[1]] == 1) 
        && 
        ((rcp[0] + 1) > 9 || matrix_rm[(rcp[0] + 1)][rcp[1]] == 1)
         && 
        ((rcp[1] - 1) < 0 || matrix_rm[(rcp[0])][(rcp[1] - 1)] == 1)
         && 
        ((rcp[1] + 1) > 9 || matrix_rm[(rcp[0])][(rcp[1] + 1)] == 1)) {
            printf("\nROVER INSIDE KNOWN AREA");
            break;
        }

    // select of moving: left (1)/right (2)/down (3)/up (4)
    srand(srand_arg); mv = (rand() % 4) + 1;
    printf("mv = %d -> move to: ", mv); move_name(mv);
    
    nextRcp[0] = rcp[0]; // row (y)
    nextRcp[1] = rcp[1]; // column (x)

    if (mv == 1){
        if ((rcp[1] - 1) >= 0){
            nextRcp[1] = rcp[1] - 1; nextRcp[0] = rcp[0];
        }     
    }
    else if (mv == 2){
        if ((rcp[1] + 1) <= 9){
            nextRcp[1] = rcp[1] + 1; nextRcp[0] = rcp[0];
        }     
    }
    else if (mv == 3){
        if ((rcp[0] + 1) <= 9){
            nextRcp[0] = rcp[0] + 1; nextRcp[1] = rcp[1];
        }     
    }
    else if (mv == 4){
        if ((rcp[0] - 1) >= 0){
            nextRcp[0] = rcp[0] - 1; nextRcp[1] = rcp[1];
        }     
    }

    printf("nextRcp = (%d, %d)\n", nextRcp[0], nextRcp[1]);
    
    if (setRcp[nextRcp[0]][nextRcp[1]] == 0) {
        if (nextRcp[0] != rcp[0] || nextRcp[1] != rcp[1]) {
            printf("moved to: (%d, %d)\n", nextRcp[0], nextRcp[1]);
        }
    }

    else {
        printf("(been in this area) OR (reached boundary of terrain) -> don`t move\n");
        nextRcp[0] = rcp[0]; // row (y)
        nextRcp[1] = rcp[1]; // column (x)
        srand_arg++;
        continue;
    }

    rcp[0] = nextRcp[0]; // row (y)
    rcp[1] = nextRcp[1]; // column (x)
    setRcp[rcp[0]][rcp[1]] = 1;

    for (i = 0; i < 10; i++){
        for (j = 0; j < 10; j++){
            if (setRcp[i][j] == 1)
                printf("(%d, %d) ", i, j);
        }
    }
    
// # ВИЗУАЛЬНОЕ ОТОБРАЖЕНИЕ КАРТЫ ДВИЖЕНИЯ =========================================
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (setRcp[i][j] == 1)
                matrix_rm[i][j] = 1; // i = row; j = column
        }
    }

    matrix_rm[rcp[0]][rcp[1]] = 2; // current rover position

    printf("\n\n* * 0|1|2|3|4|5|6|7|8|9 * *\n");
    printf("-----+-+-+-+-+-+-+-+-+-----\n");
    for (i = 0; i < 10; i++) {
        printf("%d | ", i);
        for (j = 0; j < 10; j++) {
            printf("%d ", matrix_rm[i][j]);
        }
        printf("| %d\n", i);
    }
    printf("-----+-+-+-+-+-+-+-+-+-----\n");
    printf("* * 0|1|2|3|4|5|6|7|8|9 * *\n");

// Ввод пользователя для следующего хода
    printf("\n[n]: ");
    scanf("%d", &ii);
    day++;
    srand_arg = time(NULL);
}
}
