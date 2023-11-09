#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
char choice;
int MaxAmount = 1000, recordednum = 0, i;
char line[100];
char* filename;
char date[11] , time[6], steps[5];
// Global variables for filename and FITNESS_DATA array


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
    printf("MENU: \n");
    printf("A: Specify the filename to be imported\n");
    printf("B: Display the total number of records in the file\n");
    printf("C: Find the date and time of the timeslot with the fewest steps\n");
    printf("D: Find the data and time of the timeslot with the largest number of steps\n");
    printf("E: Find the mean step count of all the records in the file\n");
    printf("F: Find the longest continuous period where the step count is above 500 steps\n");
    printf("Q: QUit\n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%c", &choice);

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


    switch(choice){
        case 'A':
            printf("Enter the Filename: ");
            scanf("%s", filename);
            if (filename = "FitnessData_2023.csv"){
                printf("File successfully loaded.\n");
            }
            else{
                printf("Error: Could not open file");
            }
            break;

        case 'B':
            printf("Total records: %d\n", recordednum);
            break;
        
        case 'C':

            break;

        case 'D':

            break;

        case 'E': 

            break;

        case 'F': 

            break;

        case 'Q':
            printf("QUIT\n");
            break;

        default:
            printf("Invalid choice. Try again.\n");


        
    }
   
}
