#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[50];
    char director[50];
    int releaseYear;
} Movie;

void addMovie(Movie *m, int i) {
    printf("Movie #%d\n", i + 1);
    printf("Enter the movie title: ");
    scanf(" %[^\n]", m->title);
    printf("Enter the movie director: ");
    scanf(" %[^\n]", m->director);
    printf("Enter the movie release year: ");
    scanf("%d", &m->releaseYear);
    printf("\n");
}

void displayMovie(const Movie *m, int i) {
    printf("Movie #%d\n", i + 1);
    printf("Movie Title: %s\n", m->title);
    printf("Movie Director: %s\n", m->director);
    printf("Movie Release Year: %d\n\n", m->releaseYear);
}

void saveFile(FILE *file, int movieCount, const Movie *movies) {
    file = fopen("movies.txt", "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < movieCount; i++) {
        fprintf(file, "Movie #%d\n", i + 1);
        fprintf(file, "Movie Title: %s\n", movies[i].title);
        fprintf(file, "Movie Director: %s\n", movies[i].director);
        fprintf(file, "Movie Release Year: %d\n\n", movies[i].releaseYear);
    }
    
    fclose(file);
}

void loadFile(FILE *file, Movie *movies, int *movieCount) {
    file = fopen("movies.txt", "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    *movieCount = 0; //resetting to 0 for index but will return to max value
    while (fscanf(file, "Movie #%*d\nMovie Title: %[^\n]\nMovie Director: %[^\n]\nMovie Release Year: %d\n\n", movies[*movieCount].title, movies[*movieCount].director, &movies[*movieCount].releaseYear) != EOF) {
        (*movieCount)++;
    } //using * after % will ignore the value but still read
      // EOF means end of file
    fclose(file);
}

void appendFile(FILE *file, Movie *movies){
    file = fopen("movies.txt", "a");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "Movie Title: %s\n", movies->title);
    fprintf(file, "Movie Director: %s\n", movies->director);
    fprintf(file, "Movie Release Year: %d\n\n", movies->releaseYear);
    
    fclose(file);
}

void newMovie(Movie *m, int count){
    printf("Enter the movie title: ");
    scanf(" %[^\n]", m->title);
    printf("Enter the movie director: ");
    scanf(" %[^\n]", m->director);
    printf("Enter the movie release year: ");
    scanf("%d", &m->releaseYear);
    printf("\n");

    appendFile(NULL, m);
}

void sortMovie(Movie *movies, int count){
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (strcmp(movies[j].title, movies[minIndex].title) < 0) {
                minIndex = j;
            }
        }
        // Swap movies[i] and movies[minIndex]
        Movie temp = movies[i];
        movies[i] = movies[minIndex];
        movies[minIndex] = temp;
    }
}

void readFile(FILE *file) {
    file = fopen("movies.txt", "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char content[1000];
    while (fgets(content, sizeof(content), file) != NULL) {
        printf("%s", content);
    }

    fclose(file);
}

void updateMovie(FILE *file, const char *find, Movie *movies, int *movieCount) {
    loadFile(file, movies, movieCount);

    int updated = 0; // Flag to check if any movie was updated

    for (int i = 0; i < *movieCount; i++) {
        if (strcmp(find, movies[i].title) == 0) {
            printf("Enter the updated movie title: ");
            scanf(" %[^\n]", movies[i].title);
            printf("Enter the updated movie director: ");
            scanf(" %[^\n]", movies[i].director);
            printf("Enter the updated movie release year: ");
            scanf(" %d", &movies[i].releaseYear);
            updated = 1;
            break;
        }
    }

    if (!updated) {
        printf("Movie not found.\n");
    }
}

void searchMovie(char *find, Movie *m, int *movieCount){
    int found = 0;
    for (int i = 0; i < *movieCount; i++) {
        if (strcmp(find, m[i].title) == 0) {
            displayMovie(&m[i], i);
            found = 1;
            break; // Exit loop once movie is updated
        }
    }

    if(!found){
        printf("No movie found.\n");
    }
}

int main() {
    FILE *file;
    int movieCount = 0;
    int answer;

    printf("===============================\n");
    printf(" 1 -> Create Movie Collection  \n");
    printf(" 2 -> Add Movie Collection     \n");
    printf(" 3 -> Update Movie Collection  \n");
    printf(" 4 -> Sort Movie Collection    \n");
    printf(" 5 -> Search Movie Collection  \n");
    printf(" 6 -> Show Movie Collection    \n");
    printf(" 7 -> Save Movie Collection    \n");
    printf(" 8 -> Load Movie Collection    \n");
    printf(" 9 -> Read Movie Collection    \n");
    printf(" 0 -> Exit the Program         \n");
    printf("===============================\n\n");

    do{
        printf("Enter the number to operate: ");
        scanf("%d", &answer);

        switch (answer){
            case 1: // create movie
                printf("Enter the number of movies to be inputted: ");
                scanf("%d", &movieCount);
                
                Movie *movieCollection = (Movie *)malloc(movieCount * sizeof(Movie));

                for (int i = 0; i < movieCount; i++) {
                    addMovie(&movieCollection[i], i);
                }
                saveFile(file, movieCount, movieCollection);
                break;
            case 2: // add movie
                if(file == NULL){
                    printf("No file exist. Please create file first\n");
                    answer = -1;
                    break;
                } else {
                    newMovie(&movieCollection[movieCount], movieCount);
                    movieCount++; // Increment movieCount after adding a new movie
                    saveFile(file, movieCount, movieCollection);
                    break;
                }
            case 3: // update movie
                if (movieCollection == NULL) {
                    printf("Please create a movie collection first.\n");
                    break;
                }

                char find[50];
                printf("Enter the movie title to update: ");
                scanf(" %[^\n]", find);
                updateMovie(file, find, movieCollection, &movieCount);
                saveFile(file, movieCount, movieCollection);
                break;
            case 4: // sort movie
                sortMovie(movieCollection, movieCount);
                break;
            case 5: // search movie
                loadFile(file, movieCollection, &movieCount);

                printf("Enter to find movie: ");
                scanf(" %[^\n]", find);
                searchMovie(find, movieCollection, &movieCount);
                break;
            case 6: // display movie
                for (int i = 0; i < movieCount; i++) {
                    displayMovie(&movieCollection[i], i);
                }
                break;
            case 7: // save file
                saveFile(file, movieCount, movieCollection);
                break;
            case 8: // load file
                loadFile(file, movieCollection, &movieCount);
                break;
            case 9: // read file
                readFile(file);
                break;
        }
    } while (answer != 0);

    return 0;
}
