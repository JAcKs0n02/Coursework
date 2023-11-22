#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here

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
    if (token != NULL) {strcpy(date, token);
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
FITNESS_DATA records[100];
int recordednum = 0, i;

void ImportedFile() {
    FILE *file = fopen("FitnessData_2023.csv", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open the file.\n");
        return;
    }
    
    char line[100];
    char date[11] , time[6], steps[5];

    while(fgets(line,30,file)){
    tokeniseRecord(line, ",", date, time, steps);
    strcpy(records[recordednum].date, date);
    strcpy(records[recordednum].time, time);
    records[recordednum].steps=atoi(steps);
    recordednum++;
    }
   
    fclose(file);
}

void A_CheckFilename() {
    ImportedFile();

    char inputname[] = "FitnessData_2023.csv";
    char CheckName[100];
    printf("Enter the Filename: ");
        scanf("%s", CheckName);
        if (strcmp(CheckName, inputname)){
            printf("Error: Could not open file\n");
        }
        else{
            printf("File successfully loaded.\n");
        }
}

void B_TotalNum() {
    ImportedFile();
    printf("Total records: %d\n", recordednum);
}

void C_FewestSteps() {
    ImportedFile();
    int min;
    int Num;

    min = records[0].steps;
    for (i = 0; i < recordednum; i++){
        if (records[i].steps < min){
            min = records[i].steps;
            Num = i;
        }
    }
    printf("Fewest steps: %s %s\n", records[Num].date, records[Num].time);
}

void D_LargestSteps() {
    ImportedFile();
    int Max;
    int Num = 0;

    Max = records[0].steps;
    for (i = 1; i < recordednum; i++){
        if (records[i].steps > Max){
            Max = records[i].steps;
            Num = i;
        }
    }
    printf("Largest steps: %s %s\n", records[Num].date, records[Num].time);

}


int main() {
    char choice;
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

    switch(choice){
        case 'A':
        case 'a':
            A_CheckFilename();
            break;

        case 'B':
        case 'b':
            B_TotalNum();
            break;
        
        case 'C':
        case 'c':
            C_FewestSteps();
            break;

        case 'D':
        case 'd':
            D_LargestSteps();
            break;

        case 'E':
        case 'e':

            break;

        case 'F':
        case 'f': 

            break;

        case 'Q':
        case 'q':
            printf("QUIT\n");
            break;

        default:
            printf("Invalid choice. Try again.\n");


        
    }
    
}
