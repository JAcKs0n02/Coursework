#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Record {
    char timestamp[256];
    int stepCount;
} Record;

void readDataFile(const char* filename, Record* records, int* numRecords) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Error: File not found: %s\n", filename);
        exit(1);
    }

    *numRecords = 0;
    while (!feof(f)) {
        Record record;
        int len = fscanf(f, "%s %d\n", record.timestamp, &record.stepCount);
        if (len != 2) {
            break;
        }

        records[*numRecords] = record;
        (*numRecords)++;
    }

    fclose(f);
}

void writeSortedDataFile(const char* filename, Record* records, int numRecords) {
    FILE* f = fopen((filename + ".tsv"), "w");
    if (!f) {
        printf("Error: Unable to open file: %s.tsv\n", filename);
        exit(1);
    }

    for (int i = 0; i < numRecords; i++) {
        fprintf(f, "%s\t%d\n", records[i].timestamp, records[i].stepCount);
    }

    fclose(f);
}

int main() {
    const char* filename;
    Record* records;
    int numRecords;

    printf("Enter Filename: ");
    scanf("%s", filename);

    readDataFile(filename, records, &numRecords);

    if (numRecords == 0) {
        printf("Error: File is empty.\n");
        exit(1);
    }

    qsort(records, numRecords, sizeof(Record), cmpByStepCount);

    writeSortedDataFile(filename, records, numRecords);

    free(records);

    return 0;
}

int cmpByStepCount(const void* rec1, const void* rec2) {
    Record* record1 = (Record*)rec1;
    Record* record2 = (Record*)rec2;

    return record2->stepCount - record1->stepCount;
}
