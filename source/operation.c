/**
 * @file operation.c
 * @author Nuno Araújo (a20078@alunos.ipca.pt)
 * @brief Operation main file
 * @version 0.1
 * @date 27-04-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "lib/lib.h"

/**
 * @brief Check if operation exists 
 * @param head 
 * @param cod 
 * @return true 
 * @return false 
 */
bool checkOp(Operation* head, int number)
{
    if (head == NULL) return false;
    Operation* aux = head;

    while (aux != NULL) 
    {
		if (aux->id == number) return true;
		aux = aux->next;
	}
	return false;    
}

/**
 * @brief Create operation 
 * @return Operation* 
 */
Operation* createOp()
{
    Operation *Op = (Operation*)malloc(sizeof(Operation));
    Op->next = NULL;
    return Op;
}

/**
 * @brief Insert operation
 * @param head 
 * @param new 
 * @return Operation* 
 */
Operation* insertOp(Operation* head, Operation* new)
{
    if (checkOp(head, new->id)) return head;
    if(head == NULL) head = new;      
    else                                                         
    {
        Operation* aux = head;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }  
        aux->next = new;
    }
    return head;  
}

/**
 * @brief Remove operation
 * @param head 
 * @param id 
 * @return Operation* 
 */
Operation* removeOp(Operation* head, int id)
{
    if (head == NULL) return NULL;

    Operation* aux = head;
    Operation* auxPrev = NULL;

    while (aux && aux->id != id)
    {
        auxPrev = aux;
        aux = aux->next;
    }

    if (auxPrev == NULL)
    {
        head = head->next;
        free(aux);
    }
    else
    {
        auxPrev->next = aux->next;
        free(aux);
    }
}

/**
 * @brief Change Operation
 * @param head 
 * @param cod 
 * @return Operation* 
 */
Operation* changeOp(Operation* head, Operation* new)
{
    Operation* operation = head;

    if (head == NULL) return NULL;
    
    while (operation && operation->id != new->id)
    {
        operation = operation->next;
    }
    
    if (operation->id == new->id)
    {
        operation->mac = new->mac;
    }
    return head;
}

/**
 * @brief Show operations recursively
 * 
 * @param head 
 */
void showOp(Operation* head)
{
    if (head == NULL) return;
    printf("OPERATION: %d\n", head->id);
    showMac(head->mac);
    showOp(head->next);
}