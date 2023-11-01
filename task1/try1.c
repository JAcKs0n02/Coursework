#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a data structure to store each record
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessRecord;

int main() {
    // Open the CSV file for reading
    FILE *file = fopen("FitnessData_2023.csv", "r");
    
    if (file == NULL) {
        printf("File not found or cannot be opened.\n");
        return 1;
    }
    
    // Read and store the records in an array
    int maxRecords = 1000;  // Adjust this based on your data size
    FitnessRecord records[maxRecords];
    int recordCount = 0;
    
    char line[30];  // Assuming the longest line is 30 characters
    while (fgets(line, sizeof(line), file) && recordCount < maxRecords) {
        sscanf(line, "%10[^,],%5[^,],%d", records[recordCount].date, records[recordCount].time, &records[recordCount].steps);
        recordCount++;
    }
    
    // Close the file
    fclose(file);

    // Print the number of records
    printf("Number of records in file: %d\n", recordCount);
    
    // Print the first three records
    for (int i = 0; i < 3 && i < recordCount; i++) {
        printf("%s/%s/%d\n", records[i].date, records[i].time, records[i].steps);
    }
    
    return 0;
}
