#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data {
    char name[100];
    int step_count;
} Data;

void readData(const char *filename, Data **data) {
    // Open the input CSV file
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error opening input file: %s\n", filename);
        exit(1);
    }

    // Allocate memory for the entire dataset
    int size = 100; // Estimated size of the dataset
    Data *tempData = (Data *)calloc(size, sizeof(Data));
    (*data) = tempData;

    // Read data rows into the tempData array
    int i = 0;
    while (!feof(fp)) {
        if (i == size) {
            // Reallocate memory if the tempData array is full
            size *= 2;
            Data *newData = (Data *)calloc(size, sizeof(Data));
            memcpy(newData, tempData, i * sizeof(Data));
            free(tempData);
            tempData = newData;
            (*data) = tempData;
        }

        fscanf(fp, "%[^,],%d\n", tempData[i].name, &tempData[i].step_count);
        i++;
    }

    // Close the file
    fclose(fp);
}

void sortData(Data **data, int size) {
    // Implement insertion sort or another sorting algorithm to sort the data
    for (int i = 1; i < size; i++) {
        Data tmp = (*data)[i];
        int j = i - 1;
        while (j >= 0 && (*data)[j]->step_count < tmp.step_count) {
            (*data)[j + 1] = (*data)[j];
            j--;
        }
        (*data)[j + 1] = tmp;
    }
}

void writeData(const char *filename, Data *data, int size) {
    // Open the output CSV file
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Error opening output file: %s\n", filename);
        exit(1);
    }

    // Write sorted data to the output file, including all fields
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%s,%d,%.2f\n",
                data[i].name, data[i].step_count,
                (float)data[i].step_count / 1000.0); // Add a calculated field: step_count in kilometers
    }

    // Close the file
    fclose(fp);
}

int main() {
    // Prompt for input and output filenames
    const char *inputFilename;
    const char *outputFilename;
    printf("Enter input filename: ");
    scanf("%s", inputFilename);
    printf("Enter output filename: ");
    scanf("%s", outputFilename);

    // Read data from the input file
    Data *data;
    readData(inputFilename, &data);
    int size = sortData(data);

    // Sort the data by step count in descending order
    sortData(&data, size);

    // Write sorted data to the output file
    writeData(outputFilename, data, size);

    // Free the allocated memory
    writeData(data);

    printf("Output file created: %s\n", outputFilename);

    return 0;
}
