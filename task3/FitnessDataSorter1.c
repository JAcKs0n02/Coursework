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

int compareFitnessData(const void *data1, const void *data2) {
    FitnessData *p1 = (FitnessData *)data1;
    FitnessData *p2 = (FitnessData *)data2;
    return (p2->steps - p1->steps);
}

int main() {
    char inputFilename[80];

    printf("Enter Filename: ");
    scanf("%s", inputFilename);


    FILE *fp = fopen(inputFilename, "r");
    if (!fp) {
        printf("Error opening input file: %s\n", inputFilename);
        exit(1);
    }

    int numRecords = 0;
    FitnessData *data = malloc(sizeof(FitnessData));

    while (!feof(fp)) {
        if (numRecords == sizeof(data) / sizeof(FitnessData)) {
            FitnessData *tempData = malloc(2 * sizeof(FitnessData));
            memcpy(tempData, data, numRecords * sizeof(FitnessData));
            free(data);
            data = tempData;
        }

        char record[100];
        fgets(record, 100, fp);
        tokeniseRecord(record, ',', data[numRecords].date, data[numRecords].time, &data[numRecords].steps);
        numRecords++;
    }

    fclose(fp);

    qsort(data, numRecords, sizeof(FitnessData), compareFitnessData);


    FILE *fp2 = fopen((strcat(inputFilename, ".tsv")), "w");
    if (!fp2) {
        printf("Error opening output file: %s\n", strcat(inputFilename, ".tsv"));
        exit(1);
    }

    for (int i = 0; i < numRecords; i++) {
        fprintf(fp2, "%s\t%s\t%d\n", data[i].date, data[i].time, data[i].steps);
    }

    free(data);

    return 0;
}
