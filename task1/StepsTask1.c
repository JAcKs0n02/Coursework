#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here
int MaxAmount = 1000, recordednum = 0, i;
char line[100];
char date[11] , time[6], steps[5];


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

int main() {
    FILE *file = fopen("FitnessData_2023.csv", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open the file.\n");
        return 1;
    }

    FITNESS_DATA records[MaxAmount];
     
    while(fgets(line,30,file)){
    tokeniseRecord(line, ",", date, time, steps);
    strcpy(records[recordednum].date, date);
    strcpy(records[recordednum].time, time);
    records[recordednum].steps=atoi(steps);
    recordednum++;
    }
   
    fclose(file);

    printf("Number of records in file: %d\n", recordednum);

    for (i = 0; i < 3; i++){
        printf("%s/%s/%d\n", records[i].date, records[i].time, records[i].steps);
    }
    return 0;

}
