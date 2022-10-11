/**
 * @file machine.c
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
bool checkMa(Machine* head, int cod)
{
    if (head == NULL) return false;
    Machine* aux = head;

    while (aux != NULL) 
    {
		if (aux->id == cod) return true;
		aux = aux->next;
	}
	return false;    
}

/**
 * @brief Create machine 
 * @return Machine* 
 */
Machine* createMa()
{
    Machine *Ma = (Machine*)malloc(sizeof(Machine));
    Ma->next = NULL;
    return Ma;
}

/**
 * @brief Insert machine (in the tail)
 * @param head 
 * @param new 
 * @return Machine* 
 */
Machine* insertMa(Machine* head, Machine* new)
{
    if (checkMa(head, new->id)) return head;
    if(head == NULL) head = new;      
    else                                                         
    {
        Machine* aux = head;
        while (aux->next != NULL) { aux = aux->next; }  
        aux->next = new;
    }
    return head;
}

/**
 * @brief Remove machine
 * @param head 
 * @param cod 
 * @return Machine* 
 */
Machine* removeMa(Machine* head, int cod)
{
    if (head == NULL) return NULL;

    Machine* aux = head;
    Machine* auxPrev = NULL;

    while (aux && aux->id != cod)
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

void showMac(Machine* head)
{
    if (head == NULL) return;
    printf("MAC ID: %d | MAC TU: %d\n", head->id, head->time);
    showMac(head->next);
}