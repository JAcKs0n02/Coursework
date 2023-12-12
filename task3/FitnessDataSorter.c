#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

void openFile(){
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
int main() {
    char FileName;
    int i;

    printf("Enter Filename: ");
    scanf("%s", FileName);

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
}


