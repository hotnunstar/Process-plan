/**
 * @file operation.h
 * @author Nuno Araújo (a20078@alunos.ipca.pt)
 * @brief Operation header file
 * @version 0.1
 * @date 27-04-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef OPERATION
#define OPERATION

#include "lib.h"

typedef struct Operation
{
    int id;                                             /// Operation id
    struct Machine *mac;                                /// Machine list pointer
    struct Operation *next;                             /// Next Operation pointer
}Operation;

bool checkOp(Operation* head, int number);              /// Check if node exists
Operation* createOp();                                  /// Allocate memory
Operation* insertOp(Operation* head, Operation* new);   /// Insert node
Operation* removeOp(Operation* head, int id);           /// Remove node
Operation* changeOp(Operation* head, Operation* new);   /// Change node properties
void showOp(Operation* head);                           /// Show operations recursively

#endif