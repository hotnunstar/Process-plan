/**
 * @file lib.h
 * @author Nuno Araújo (a20078@alunos.ipca.pt)
 * @brief Generic lib
 * @version 0.1
 * @date 27-04-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef LIB
#define LIB

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "machine.h"
#include "job.h"
#include "operation.h"
#include "processPlan.h"

#define ROW 9
#define COL 60

typedef struct JobFile {
    int job;
    int op;
    int mac;
    int time;
}JobFile;

Job* readProcessPlan(char* filename);               /// Read process plan from .txt file
bool writeProcessPlan(Job* job, char* filename);    /// Write process plan on .bin file        
bool saveTreeJob(Job* root, FILE* file);            /// Write recursively
bool saveJob(Job* job, FILE* file);                 /// Write unique job
void writeArrayPlan(MachineToPlan* mac);            /// Write escalation proposal
int concatenateInt(int jobID, int opID);            /// Concatenate two integers
bool writeHTML(char* filename, char* string);       /// Write process plan table on html file

#endif



