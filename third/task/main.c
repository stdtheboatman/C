#include <stdio.h>

#include <malloc.h>

//#include <stdlib.h>
//#include <time.h>

void deleteArray(int n, int** array) {
    for(int i = 0; i < n; i++) {
        free(array[i]);
    }
    free(array);
}


void printArray(int n, int m, int **array, char* text) {
    printf("%s\n", text);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%i ", array[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}


void deleteRow(int n, int **array, int row) {
    int *deleteRow = array[row];
    for(int i = row; i < n - 1; i++) {
        array[i] = array[i + 1];
    }

    free(deleteRow);
}

void deleteCol(int n, int m, int **array, int col) {
    for(int i = 0; i < n; i++) {
        for(int j = col; j < m - 1; j++) {
            array[i][j] = array[i][j + 1];
        }

        array[i] = realloc(array[i], (m - 1) * sizeof(int));
    }
}

int isRowCorrect(int m, int **array, int row) {
    int oneCount = 0;
    for(int j = 0; j < m; j++) {
        oneCount += (array[row][j] == 1);
    }

    return (oneCount == 1 ? 0 : 1);
}

int isColCorrect(int n, int **array, int col) {
    int oneCount = 0;
    for(int i = 0; i < n; i++) {
        oneCount += (array[i][col] == 1);
    }

    return (oneCount == 1 ? 0 : 1);
}

int findAndDeleteIncorrectRow(int *n, const int *m, int **array) {
    for(int i = 0; i < *n; i++) {
        if (!isRowCorrect(*m, array, i)) {
            deleteRow(*n, array, i);
            *n = *n - 1;

            return 1;
        }
    }

    return 0;
}

int findAndDeleteIncorrectCol(const int *n, int *m, int **array) {
    for(int j = 0; j < *m; j++) {
        if (!isColCorrect(*n, array, j)) {
            deleteCol(*n, *m, array, j);
            *m = *m - 1;

            return 1;
        }
    }

    return 0;
}

int main() {


    int n, m;

    printf("Enter n, m\n");
    scanf("%i %i", &n, &m);

    int **array = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        array[i] = (int*)malloc(m * sizeof(int));
    }

    printf("Enter array\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%i", &array[i][j]);
        }
    }

    printf("\n\n");
    printArray(n, m, array, "array");
    printf("\n\n");

    int findAnyToDelete;
    do {
        findAnyToDelete = findAndDeleteIncorrectRow(&n, &m, array);
        findAnyToDelete += findAndDeleteIncorrectCol(&n, &m, array);
    }
    while(findAnyToDelete);

    printArray(n, m, array, "array after algorithm");

    deleteArray(n, array);
    return 0;
}
