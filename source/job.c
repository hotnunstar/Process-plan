/**
 * @file job.c
 * @author Nuno Araújo (a20078@alunos.ipca.pt)
 * @brief Job main file
 * @version 0.1
 * @date 27-04-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "lib/lib.h"

/**
 * @brief Find job on tree
 * 
 * @param new 
 * @param root 
 * @return Job* 
 */
Job* findJob(Job* new, Job* root) 
{
	if (root == NULL) return NULL;
	if (root->id == new->id) return root;
	else
	{
		if (root->id > new->id) return (findJob(new, root->left));
		else return (findJob(new, root->right));
	}
}

/**
 * @brief Alloc memory
 * 
 * @return Job* 
 */
Job* createJob()
{
    Job *job = (Job*)malloc(sizeof(Job));
    job->right = NULL;
	job->left = NULL;
    return job;
}

/**
 * @brief Create Job
 * 
 * @param new 
 * @return Job* 
 */
Job* newJob(Job* new)
{
	Job* job = createJob();
    if(job == NULL) return NULL;
    job->id = new->id;
    job->op = new->op;
    return job;
}

/**
 * @brief Insert Job
 * @param root
 * @param new 
 * @return Job* 
 */
Job* insertJob(Job* root, Job* new)
{
    if (root == NULL) root = newJob(new);
    else
    {
        if(root->id > new->id) root->left = insertJob(root->left, new);
        else if(root->id < new->id) root->right = insertJob(root->right, new);
        else return root;
    }
    return root;
}

/**
 * @brief Remove Job
 * @param root 
 * @param cod 
 * @return Job* 
 */
Job* removeJob(Job* root, int cod)
{
	if (root == NULL) return NULL;

	if (root->id > cod) root->left = removeJob(root->left, cod);
	else
    {
        if (root->id < cod) root->right = removeJob(root->right, cod);
		else root = removeCurrentJob(root);
    }	
	return root;
}

/**
 * @brief Remove node and rebuild the tree
 * 
 * @param root 
 * @return Job* 
 */
Job* removeCurrentJob(Job* root)
{
    Job* aux;
	if (root == NULL) return NULL;

	if (root->left == NULL && root->right == NULL) 
    {
		destroyJob(&root);
		return NULL;
	}
	else 
		if (root->left==NULL)
        {
			aux = root;
			root = root->right;
			destroyJob(&aux);
		}
		else
		{
			if (root->right == NULL)
            {	
				aux = root;
				root = root->left;
				destroyJob(&aux);
			}
			else
			{
				aux = findMin(root->right);
				root->id = aux->id;
				root->op = aux->op;
				
				root->right = removeJob(root->right, root->id);
			}
		}
	return root;
}

/**
 * @brief Destroy node
 * 
 * @param node 
 */
void destroyJob(Job** node)
{
    if(*node != NULL)
    {
        free(*node);
        *node = NULL;
    }
}

/**
 * @brief Find smaller value
 * 
 * @param root 
 * @return Job* 
 */
Job* findMin(Job* root)
{	
    if (root->left == NULL) return root;
	else return(findMin(root->left));
}

/**
 * @brief Show jobs recursively
 * 
 * @param root 
 */
void showInOrder(Job* root) 
{
	if (root == NULL) return;
	showInOrder(root->left);
	printf("\n");
	printf("JOB: %d\n", root->id);
	showOp(root->op);
	showInOrder(root->right);
}