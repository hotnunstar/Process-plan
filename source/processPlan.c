/**
 * @file processPlan.c
 * @author Nuno Araújo (a20078@alunos.ipca.pt)
 * @brief Machine main file
 * @version 0.1
 * @date 27-04-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "lib/lib.h"

/**
 * @brief Check if machine exists 
 * @param head 
 * @param cod 
 * @return true 
 * @return false 
 */
bool checkMaList(MachineToPlan* head, int id, int jobID, int opID)
{
    if (head == NULL) return false;
    MachineToPlan* aux = head;

    while (aux != NULL) 
    {
		if (aux->id == id && aux->jobID == jobID && aux->opID == opID) return true;
		aux = aux->next;
	}
	return false;    
}

/**
 * @brief Create machine (one machine for operation)
 * @return Machine* 
 */
MachineToPlan* createMaList()
{
    MachineToPlan *Ma = (MachineToPlan*)malloc(sizeof(MachineToPlan));
    Ma->next = NULL;
    return Ma;
}

/**
 * @brief Insert machine (one machine for operation)
 * @param head 
 * @param new 
 * @return Machine* 
 */
MachineToPlan* insertMaList(MachineToPlan* head, MachineToPlan* new)
{
    if (checkMaList(head, new->id, new->jobID, new->opID)) return head;
    if(head == NULL) head = new;      
    else                                                         
    {
        MachineToPlan* aux = head;
        while (aux->next != NULL) { aux = aux->next; }  
        aux->next = new;
    }
    return head;
}

/**
 * @brief Get machine list
 * 
 * @param root 
 * @return MachineToPlan* 
 */
MachineToPlan* getMacList(Job* root)
{
    if (root == NULL) return NULL;
    MachineToPlan* listHead = NULL;

    listHead = getMacListRight(root, listHead);
    listHead = getMacListLeft(root, listHead);
    
    return listHead;
}

/**
 * @brief Get machine list Left nodes
 * 
 * @param root 
 * @param listHead 
 * @return MachineToPlan* 
 */
MachineToPlan* getMacListLeft(Job* root, MachineToPlan* listHead)
{
    if (root == NULL) return listHead;
    MachineToPlan* mac;
    while(root->op)
        {
            Machine* aux = root->op->mac;
            Machine* next = root->op->mac->next;
            while (next)
            {
                if(next->time < aux->time) aux = next;
                next = next->next;
            }
            mac = createMaList();
            mac->id = aux->id;
            mac->time = aux->time;
            mac->jobID = root->id;
            mac->opID = root->op->id;
            mac->finalTime = 0;
            listHead = insertMaList(listHead, mac);
            root->op = root->op->next;
        }
    root = root->left;
    listHead = getMacListLeft(root, listHead);
    listHead = getMacListRight(root, listHead);
}

/**
 * @brief Get machine list right nodes
 * 
 * @param root 
 * @param listHead 
 * @return MachineToPlan* 
 */
MachineToPlan* getMacListRight(Job* root, MachineToPlan* listHead)
{
    if (root == NULL) return listHead;

    MachineToPlan* mac;
    while(root->op)
        {
            Machine* aux = root->op->mac;
            Machine* next = root->op->mac->next;
            while (next)
            {
                if(next->time < aux->time) aux = next;
                next = next->next;
            }
            mac = createMaList();
            mac->id = aux->id;
            mac->time = aux->time;
            mac->jobID = root->id;
            mac->opID = root->op->id;
            mac->finalTime = 0;
            listHead = insertMaList(listHead, mac);
            root->op = root->op->next;
        }
    root = root->right;
    listHead = getMacListLeft(root, listHead);
    listHead = getMacListRight(root, listHead);
}

/**
 * @brief Show machine list
 * 
 * @param head 
 */
void showMacList(MachineToPlan* head)
{
    if (head == NULL) return;
    printf("JOB ID: %d | OP ID: %d | MAC ID: %d | MAC TU: %d\n", head->jobID, head->opID, head->id, head->time);
    showMacList(head->next);
}