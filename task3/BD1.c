#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to tokenize a record into an array of strings
int tokenizeRecord(char *record, char **tokens) {
    int i = 0;
    char *p = strtok(record, ",");
    while (p) {
        tokens[i++] = p;
        p = strtok(NULL, ",");
    }
    return i;
}

// Function to process the data file, read in and sort
void processFile(char *filename) {
    FILE *fp;
    char **records = NULL;
    int numRecords = 0;

    if ((fp = fopen(filename, "r")) == NULL) {
        perror("Failed to open file");
        return;
    }

    // Read each record from the file and tokenize it
    char record[1024];
    while (fgets(record, sizeof(record), fp)) {
        char *tokens[3];
        int numTokens = tokenizeRecord(record, tokens);
        if (numTokens < 2) {
            printf("Invalid record: %s\n", record);
            continue;
        }

        // Add the record to the array
        records = realloc(records, sizeof(char *) * (numRecords + 1));
        records[numRecords] = malloc(strlen(record) + 1);
        strcpy(records[numRecords], record);
        numRecords++;
    }

    fclose(fp);

    // Sort the records in descending order based on step count
    qsort(records, numRecords, sizeof(char *), (int (*)(const void *, const void *))strcmp);

    // Write the sorted records to the output file
    char outputFilename[1024];
    strcpy(outputFilename, filename);
    strcat(outputFilename, ".tsv");
    fp = fopen(outputFilename, "w");
    for (int i = numRecords - 1; i >= 0; i--) {
        fprintf(fp, "%s\n", records[i]);
        free(records[i]);
    }
    free(records);
    fclose(fp);
}

int main() {
    char filename[1024];
    printf("Enter filename: ");
    scanf("%s", filename);
    processFile(filename);
    return 0;
}
