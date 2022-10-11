/**
 * @file machine.h
 * @author Nuno Araújo (a20078@alunos.ipca.pt)
 * @brief Machine header file
 * @version 0.1
 * @date 27-04-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MACHINE
#define MACHINE

#include "lib.h"

typedef struct Machine
{
    int id;                                         /// Machine id
    int time;                                       /// Machine operation time
    struct Machine *next;                           /// Next machine pointer
}Machine;

bool checkMa(Machine* head, int cod);               /// Check if node exists
Machine* createMa();                                /// Allocate memory
Machine* insertMa(Machine* head, Machine* new);     /// Insert node
Machine* removeMa(Machine* head, int cod);          /// Remove node
void showMac(Machine* head);                        /// Show machines recursively

#endif
