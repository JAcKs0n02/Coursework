#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

int main() {
    // Open the CSV file for reading
    FILE *file = fopen("FitnessData_2023.csv", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open the file.\n");
        return 1;
    }

// Define any additional variables here
    int MaxAmount = 1000, recordednum = 0, i;


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

// Complete the main function
    FITNESS_DATA records[MaxAmount];
     

    char line[100];
    while (fgets(line, sizeof(line), file) && recordednum < MaxAmount) {
        sscanf(line, "%10[^,],%5[^,],%d", records[recordednum].date, records[recordednum].time, &records[recordednum].steps);
        recordednum ++;
    }

    fclose(file);

    printf("Number of records in file: %d\n", recordednum);

    for (i = 0; i < 3; i++){
        printf("%s/%s/%d\n", records[i].date, records[i].time, records[i].steps);
    }
    return 0;

}
