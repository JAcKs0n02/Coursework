#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

FITNESS_DATA records[250];
int recordednum;

void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    char *inputCopy = strdup(input);
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

    free(inputCopy);
}

int ImportedFile() {
    char inputname[100];
    char line[250];
    char date[20] , time[20], steps[20];
    recordednum = 0;

    printf("Input filename: ");
    scanf("%s", inputname);
    FILE *file = fopen(inputname, "r");
    if(!file){
        printf("Error: Could not find or open the file.\n");
        return 1;
    }else{
        printf("File successfully loaded.\n");
    }
    
    while(fgets(line,100,file)){
    tokeniseRecord(line, ",", date, time, steps);
    strcpy(records[recordednum].date, date);
    strcpy(records[recordednum].time, time);
    records[recordednum].steps=atoi(steps);
    recordednum++;
    }
    fclose(file);
}


void B_TotalNum() {
    printf("Total records: %d\n", recordednum);
}

void C_FewestSteps() {
    int min;
    int Num;
    int i;

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
    int max;
    int Num = 0;
    int i;
    max = records[0].steps;
    for(i = 0; i < recordednum; i++){
        if(records[i].steps > max){
            max = records[i].steps;
            Num = i;
        }
    }
    printf("Largest steps: %s %s\n", records[Num].date, records[Num].time);
}

void E_MeanSteps (){
    int totalSteps = 0;
    int i;

    for (i = 0; i < recordednum; i++) {
        totalSteps += records[i].steps;
    }

    float mean = (float)totalSteps / recordednum;
    printf("Mean step count: %.0f\n", mean);
}

void F_StepsAbove500() {
    int longestCount = 0;
    int count = 0;
    int startIdx = 0;
    int i;

    for (i = 0; i < recordednum; i++) {
        if (records[i].steps > 500) {
            count++;
            if (count > longestCount) {
                longestCount = count;
                startIdx = i - count + 1;
            }
        } else {
            count = 0;
        }
    }

    if (longestCount > 0) {
        printf("Longest period start: %s %s\n", records[startIdx].date, records[startIdx].time);
        printf("Longest period end: %s %s\n", records[startIdx + longestCount - 1].date, records[startIdx + longestCount - 1].time);
    } 
}


int main() {
    char choice;

    while (1){
        printf("MENU: \n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the data and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: QUit\n");

        printf("Enter your choice: ");
        scanf("%c", &choice);

        switch(choice){
            case 'A':
            case 'a':
                if(ImportedFile() == 1){
                    return 1;
                }
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
                E_MeanSteps();
                break;

            case 'F':
            case 'f': 
                F_StepsAbove500();
                break;

            case 'Q':
            case 'q':
            return 0;

            default:
            printf("Invalid choice. Try again.\n");

        }
        
        while (getchar() != '\n');
        
    }
    return 0;
}
