/**
 * @file job.h
 * @author Nuno Araújo (a20078@alunos.ipca.pt)
 * @brief Job header file
 * @version 0.1
 * @date 27-04-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef JOB
#define JOB

#include "lib.h"

typedef struct Job
{
    int id;                             /// Job id
    struct Operation* op;               /// Operations list pointer
    struct Job* left;                   /// Left node pointer
    struct Job* right;                  /// Right node pointer
}Job;

Job* findJob(Job* new, Job* root);      /// Find node
Job* createJob();                       /// Allocate memory
Job* newJob(Job* new);                  /// Create node
Job* insertJob(Job* root, Job* new);    /// Insert node
Job* removeJob(Job* root, int cod);     /// Remove node
Job* removeCurrentJob(Job* root);       /// Aux function to remove node
void destroyJob(Job** node);            /// Destroy node
Job* findMin(Job* root);                /// Find minimum value
void showInOrder(Job* root);            /// Show tree in order

#endif