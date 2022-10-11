/**
 * @file main.c
 * @author Nuno Araújo (a20078@alunos.ipca.pt)
 * @brief Main file
 * @version 0.1
 * @date 27-04-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "lib/lib.h"

int main()
{  
    Job* job = NULL;
    MachineToPlan* macToPlan = NULL;

    job = readProcessPlan("./txt/ProcessPlan2.txt");     /// Read process plan txt file
    //showInOrder(job);                                    /// Show process plan previous read
    macToPlan = getMacList(job);                         /// Get machines with less time for operation
    //showMacList(macToPlan);                              /// Show previous machine list
    writeArrayPlan(macToPlan);                           /// Write process plan array

    #pragma region INSERT JOB WITH TESTE DATA 
    // Machine mDataTeste1 = {1, 7};
    // Machine mDataTeste2 = {3, 5};
    // Machine mDataTeste3 = {2, 6};
    // Machine mDataTeste4 = {4, 5};
    // Machine* mh1 = NULL;
    // Machine* mh2 = NULL;
    // Operation* oh = NULL;
    // Job* jh = NULL;

    // mh1 = insertMa(mh1, &mDataTeste1);
    // mh1 = insertMa(mh1, &mDataTeste2);
    // mh2 = insertMa(mh2, &mDataTeste3);
    // mh2 = insertMa(mh2, &mDataTeste4);

    // Operation oDataTest1 = {1, mh1};
    // Operation oDataTest2 = {2, mh2};
    // oh = insertOp(oh, &oDataTest1);
    // oh = insertOp(oh, &oDataTest2);

    // Job jDataTest = {9, oh};
    // job = insertJob(job, &jDataTest);
    // showInOrder(job);
    #pragma endregion

    #pragma region REMOVE JOB
    //job = removeJob(job, 4);
    //showInOrder(job);
    #pragma endregion

    #pragma region CHANGE OPERATIONS
    //Operation oDataTest3 = {2, mh1};
    //changeOp(oh, &oDataTest3);
    //showInOrder(job);
    #pragma endregion

    #pragma region REMOVE OPERATION
    //removeOp(oh, 2);
    //showInOrder(job);
    #pragma endregion

    writeProcessPlan(job, "./txt/ProcessPlan.bin");
   
    printf("\nPress any key to exit...\n");
    getchar();
    
    return 0;
}