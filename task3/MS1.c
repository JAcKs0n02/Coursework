#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int compare(const void *a, const void *b) {
    char **row1 = (char **)a;
    char **row2 = (char **)b;
    int step_count1 = atoi(row1[2]);
    int step_count2 = atoi(row2[2]);
    return step_count2 - step_count1;
}

void sort_tsv_file() {
    char filename[MAX_LINE_LENGTH];
    printf("Enter Filename: ");
    fgets(filename, MAX_LINE_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    FILE *tsvfile = fopen(filename, "r");
    if (tsvfile == NULL) {
        printf("%s not found.\n", filename);
        return;
    }
    char output_filename[MAX_LINE_LENGTH];
    strcpy(output_filename, filename);
    char *dot = strrchr(output_filename, '.');
    if (dot != NULL) {
        *dot = '\0';
    }
    strcat(output_filename, ".tsv");
    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Error creating output file.\n");
        return;
    }
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, tsvfile);
    fprintf(output_file, "%s", line);
    char *rows[MAX_LINE_LENGTH];
    int i = 0;
    while (fgets(line, MAX_LINE_LENGTH, tsvfile)) {
        rows[i] = malloc(strlen(line) + 1);
        strcpy(rows[i], line);
        i++;
    }
    qsort(rows, i, sizeof(char *), compare);
    for (int j = 0; j < i; j++) {
        fprintf(output_file, "%s", rows[j]);
        free(rows[j]);
    }
    fclose(tsvfile);
    fclose(output_file);
    printf("Sorted data has been written to %s\n", output_filename);
}

int main() {
    sort_tsv_file();
    return 0;
}
