#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char lineage[50];
    int population;
    char name[50];
} Race;

void createText(Race *list, int i){
    printf("Enter the race: ");
    scanf(" %[^\n]", list->lineage);
    printf("Enter the population: ");
    scanf("%d", &list->population);
    printf("Enter the leader name: ");
    scanf(" %[^\n]", list->name);
    printf("\n");
}

// size = 1

void appendFile(FILE *file, Race *list, int *size){
    file = fopen("Race.txt", "a");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    createText(list, *size);

    fprintf(file, "Race #%d:\n", size);
    fprintf(file, "Lineage: %s\n", list->lineage);
    fprintf(file, "Population: %d\n", list->population);
    fprintf(file, "Leader Name: %s\n\n", list->name);

    fclose(file);
}

void saveFile(FILE *file, Race *list, int size){
    file = fopen("Race.txt", "w");

    for(int i = 0; i < size; i++){
        fprintf(file, "Race #%d:\n", i + 1);
        fprintf(file, "Lineage: %s\n", list[i].lineage);
        fprintf(file, "Population: %d\n", list[i].population);
        fprintf(file, "Leader Name: %s\n\n", list[i].name);
    }

    fclose(file);
}

void loadFile(FILE *file, Race *list, int *size){
    file = fopen("Race.txt", "r");

    if(file == NULL){
        printf("Error in opening the text file!");
        return;
    }

    *size = 0;
    while(fscanf(file, "Race #%*d:\nLineage: %[^\n]\nPopulation: %d\nLeader Name: %[^\n]\n\n", list[*size].lineage, &list[*size].population, list[*size].name) != EOF){
        (*size)++;
    }

    fclose(file);
}

void printStruct(Race *list, int size){
    for(int i = 0; i < size; i++){
        printf("Race #%d:\n", i + 1);
        printf("Lineage: %s\n", list[i].lineage);
        printf("Population: %d\n", list[i].population);
        printf("Leader Name: %s\n\n", list[i].name);
    }
}

int main(){
    int userAnswer;
    FILE *file;
    int size = 0;

    printf("================================\n");
    printf("        Operation Numbers       \n");
    printf("================================\n");
    printf("  1 -> Create Race Informations \n");
    printf("  2 -> Add Race Informations    \n");
    printf("  3 ->                          \n");
    printf("================================\n");

    do {
        printf("Enter a number: ");
        scanf("%d", &userAnswer);

        switch(userAnswer){
            case 1:
                printf("Enter the number of people to be enter: ");
                scanf("%d", &size);

                Race *list = (Race*)malloc(size * sizeof(Race));
                for(int i = 0; i < size; i++){
                    createText(&list[i], i);
                }

                saveFile(file, list, size);
                break;
            case 2:
                appendFile(file, &list[size], &size);
                size++;
                saveFile(file, list, size);
                break;
            case 3:
                saveFile(file, list, size);
                break;
            case 4:
                loadFile(file, list, &size);
                break;
            case 5:
                printStruct(list, size);
                break;
            default:
                printf("Please enter the correct number!\n");
        }
    } while(userAnswer != 0);

    return 0;
}