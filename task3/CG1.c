#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000
#define MAX_LEN 256

// Tokenize a record
void tokenizeRecord(char *record, char *tokens[]) {
    char *token = strtok(record, ",");
    int i = 0;
    while (token != NULL && i < MAX_COLS) {
        tokens[i++] = token;
        token = strtok(NULL, ",");
    }
}

// Structure to hold data rows
typedef struct {
    char *columns[MAX_COLS];
} DataRow;

// Read data from a file and sort it by step count in descending order
void sortData(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found. Please enter a valid filename.\n");
        return;
    }

    char line[MAX_LEN];
    DataRow data[MAX_ROWS];
    int num_rows = 0;

    // Read data from the file
    while (fgets(line, sizeof(line), file) != NULL && num_rows < MAX_ROWS) {
        data[num_rows].columns[0] = strdup(strtok(line, "\n"));
        char *tokens[MAX_COLS];
        tokenizeRecord(line, tokens);
        for (int i = 0; i < MAX_COLS; i++) {
            data[num_rows].columns[i] = strdup(tokens[i]);
        }
        num_rows++;
    }
    fclose(file);

    // Sort data by step count in descending order
    for (int i = 0; i < num_rows - 1; i++) {
        for (int j = i + 1; j < num_rows; j++) {
            int steps_i = atoi(data[i].columns[2]); // Assuming step count is in the third column
            int steps_j = atoi(data[j].columns[2]);
            if (steps_i < steps_j) {
                DataRow temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }

    // Write sorted data to a new .tsv file
    char *output_filename = strtok(filename, ".");
    strcat(output_filename, ".tsv");
    file = fopen(output_filename, "w");
    if (file == NULL) {
        printf("Error creating the output file.\n");
        return;
    }

    // Write sorted records to the output file
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            fprintf(file, "%s", data[i].columns[j]);
            if (j < MAX_COLS - 1) {
                fprintf(file, "\t");
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);

    printf("Sorted data has been written to %s\n", output_filename);
}

// Main function to provide a menu for user input
int main() {
    char filename[MAX_LEN];
    printf("Enter Filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline character

    sortData(filename);

    return 0;
}
