#include <stdio.h>
#include <mlang.h>

int strSize(char *str) {
    char *yk = str;
    int size = 0;

    while(*yk) {
        size++;
        yk = yk + 1;
    }

    return size;
}

char separators[] = ", .![]\n";

int isSeparator(char sym) {
    for(int i = 0; i < strSize(separators); i++) {
        if (sym == separators[i]) {
            return 1;
        }
    }

    return 0;
}

char *strCopy(char *str) {
    int size = strSize(str);
    char *result = malloc((size + 1) * sizeof(char));

    for(int i = 0; i < size; i++) {
        result[i] = str[i];
    }
    result[size] = '\0';

    return result;
}

int stringEqual(char *a, char *b) {
    int sizeA = strSize(a);
    int sizeB = strSize(b);

    if (sizeA != sizeB) {
        return 0;
    }

    for(int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}

char *sortString(char *str) {
    char *strSorted = strCopy(str);

    int size = strSize(strSorted);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size - 1 - i; j++) {
            if (strSorted[j] > strSorted[j + 1]) {
                char temp = strSorted[j];
                strSorted[j] = strSorted[j + 1];
                strSorted[j + 1] = temp;
            }
        }
    }

    return strSorted;
}

char *group[512][512];
int groupSize[512];
int groupNow = 0;

void addToGroup(char *word) {
    char *wordSorted = sortString(word);

    int isContain = 0;
    for(int i = 0; i < groupNow; i++) {
        if (stringEqual(wordSorted, sortString(group[i][0]))) {
            group[i][groupSize[i]++] = word;

            isContain = 1;
            break;
        }
    }

    if (!isContain) {
        int i = groupNow++;

        group[i][groupSize[i]++] = word;
    }
}

int main() {
    FILE *file;
    file = fopen("../input.txt", "r");

    if (file == NULL) {
        printf("file not open\n");
    }

    int bufferSize = 1024;
    char buffer[1024];
    while (fgets(buffer, bufferSize, file) != NULL) {
        char word[128];
        int yk = 0;

        for(int i = 0; i < bufferSize; i++) {
            if (buffer[i] == NULL) {
                break;
            }

            if (isSeparator(buffer[i])) {
                if (yk) {
                    word[yk] = '\0';

                    addToGroup(strCopy(word));

                    yk = 0;
                }
            }
            else {
                word[yk++] = buffer[i];
            }
        }

        if (yk) {
            word[yk] = '\0';

            addToGroup(strCopy(word));
        }
    }

    for(int i = 0; i < groupNow; i++) {
        printf("group %i\n", i + 1);
        for(int j = 0; j < groupSize[i]; j++) {
            printf("%s\n", group[i][j]);
        }

        printf("\n");
    }


    
    for(int i = 0; i < groupNow; i++) {
        for(int j = 0; j < groupSize[i]; j++) {
            free(group[i][j]);
        }
    }

    fclose(file);
    return 0;
}
