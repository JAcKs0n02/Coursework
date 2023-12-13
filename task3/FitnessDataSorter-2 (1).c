#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;


void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

int compareFitnessData(const void *a, const void *b) {
    FitnessData *dataA = (FitnessData *)a;
    FitnessData *dataB = (FitnessData *)b;

    // For descending order, compare B with A
    return dataB->steps - dataA->steps;
}

int main() {
    char inputFilename[80];
    char record[100];
    int numRecords = 0;
    FitnessData data[200];

    printf("Enter Filename: ");
    scanf("%s", inputFilename);

    FILE *fp = fopen(inputFilename, "r");
    if (!fp) {
        printf("Error opening input file: %s\n", inputFilename);
        return 1;
    }

    while (fgets(record, 200, fp)) {
        tokeniseRecord(record, ',', data[numRecords].date, data[numRecords].time, &data[numRecords].steps);
        numRecords++;
    }
    fclose(fp);

    qsort(data, numRecords, sizeof(FitnessData), compareFitnessData);

    FILE *fp2 = fopen((strcat(inputFilename, ".tsv")), "w");
    if (!fp2) {
        printf("Error opening output file: %s\n", strcat(inputFilename, ".tsv"));
        return 1;;
    }

    for (int i = 0; i < numRecords; i++) {
        fprintf(fp2, "%s\t%s\t%d\n", data[i].date, data[i].time, data[i].steps);
    }

    fclose (fp2);

    return 0;
}




