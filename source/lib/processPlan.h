/**
 * @file processPlan.h
 * @author Nuno Araújo (a20078@alunos.ipca.pt)
 * @brief Machine header file
 * @version 0.1
 * @date 27-04-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PP
#define PP

#include "lib.h"

typedef struct MachineToPlan
{
    int id;                             /// Machine ID
    int time;                           /// Machine time units
    int jobID;                          /// Job ID
    int opID;                           /// Operation ID
    int finalTime;                      /// Final operation time (used on array)
    struct MachineToPlan *next;         /// Next MachineToPlan pointer
}MachineToPlan;


bool checkMaList(MachineToPlan* head, int id, int jobID, int opID);     /// Check if node exists
MachineToPlan* createMaList();                                          /// Alocate memory    
MachineToPlan* insertMaList(MachineToPlan* head, MachineToPlan* new);   /// Insert node
MachineToPlan* getMacList(Job* root);                                   /// Get list recursively
MachineToPlan* getMacListLeft(Job* root, MachineToPlan* listHead);      /// Get left nodes from the tree  
MachineToPlan* getMacListRight(Job* root, MachineToPlan* listHead);     /// Get right nodes from the tree
void showMacList(MachineToPlan* head);                                  /// Show nodes

#endif