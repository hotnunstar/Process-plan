/**
 * @file lib.c
 * @author Nuno Araújo (a20078@alunos.ipca.pt)
 * @brief Lib main file
 * @version 0.1
 * @date 27-04-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "lib/lib.h"

/**
 * @brief Read ProcessPlan
 * 
 * @param filename 
 * @return Job* 
 */
Job* readProcessPlan(char* filename)
{
    FILE *file;
    Job* jobRoot = NULL;
    Job* job;
    Operation* opHead = NULL;
    Operation* op;
    Machine* macHead = NULL;
    Machine* mac;
    char aux[200];
    char* data;
    int jobID, opID, macID, macUT;

    if((file = fopen(filename, "r")) == NULL)
    {
        printf("Error opening file..");
        return 0;
    }
    else
    {
        (fgets(aux, sizeof(aux), file) == NULL); /// Skip first line
        while(fgets(aux, sizeof(aux), file) != NULL)
        {
            data = strtok(aux, ";");
            jobID = atoi(data);
            data = strtok(NULL, ";");
            opID= atoi(data);
            data = strtok(NULL, ";");
            macID = atoi(data);
            data = strtok(NULL, "\0");
            macUT = atoi(data);
            
            if ((jobRoot != NULL) && (job->id == jobID))
            {
                if(op->id == opID)
                {
                    mac = createMa();
                    mac->id = macID;
                    mac->time = macUT;
                    macHead = insertMa(macHead, mac);
                }
                if (op->id != opID)
                {
                    macHead = NULL;
                    op = createOp();
                    mac = createMa();

                    mac->id = macID;
                    mac->time = macUT;
                    macHead = insertMa(macHead, mac);

                    op->id = opID;
                    op->mac = macHead;
                    opHead = insertOp(opHead, op);
                }
            }
            if ((jobRoot != NULL) && (job->id != jobID))
            {
                macHead = NULL;
                opHead = NULL;
                job = createJob();
                op = createOp();
                mac = createMa();

                mac->id = macID;
                mac->time = macUT;
                macHead = insertMa(macHead, mac);

                op->id = opID;
                op->mac = macHead;
                opHead = insertOp(opHead, op);
                
                job->op = opHead;
                job->id = jobID;
                jobRoot = insertJob(jobRoot, job);
            }
            if(jobRoot == NULL)
            {
                job = createJob();
                op = createOp();
                mac = createMa();

                mac->id = macID;
                mac->time = macUT;
                macHead = insertMa(macHead, mac);

                op->id = opID;
                op->mac = macHead;
                opHead = insertOp(opHead, op);
                
                job->op = opHead;
                job->id = jobID;
                jobRoot = insertJob(jobRoot, job);
            }
        }    
    }
    fclose(file);
    return jobRoot;
}	

/**
 * @brief Write ProcessPlan
 * 
 * @param root 
 * @param filename 
 * @return true 
 * @return false 
 */
bool writeProcessPlan(Job* root, char* filename)
{
    if (root == NULL) return false;
    FILE* file = fopen(filename, "wb");
    if (file == NULL) return false;
    saveTreeJob(root, file);
    fclose(file);
    return true;
}

/**
 * @brief Save ProcessPlan
 * 
 * @param root 
 * @param file 
 */
bool saveTreeJob(Job* root, FILE* file)
{
    if(root == NULL) return false;
    saveJob(root, file);
    saveTreeJob(root->left, file);
    saveTreeJob(root->right, file);
}

/**
 * @brief Save single position from ProcessPlan
 * 
 * @param job 
 * @param file 
 * @return true 
 * @return false 
 */
bool saveJob(Job* job, FILE* file)
{
    Operation* aux = job->op;
    JobFile node;

    while (aux != NULL)
    {
        node.op = aux->id;
        node.job = job->id;
        Machine* mac = aux->mac;
        while (mac)
        {
            node.mac = mac->id;
            node.time = mac->time;
            fwrite(&node, sizeof(JobFile), 1, file);
            mac = mac->next;
        } 
        aux = aux->next; 
    }
    return true;
}

/**
 * @brief Write escalation proposal
 * 
 * @param mac 
 * @return char
 */
void writeArrayPlan(MachineToPlan* mac)
{
    if (mac == NULL) return;
    int array[ROW][COL] = {0};
    MachineToPlan* aux = mac;
    mac = mac->next;

    int value =  concatenateInt(aux->jobID, aux->opID);
    int tu = aux->time;
    for (int i = 1; i < COL; i++)
    {
        array[aux->id][i] = value;
        tu --;
        if(tu == 0)
        {
            aux->finalTime = i;
            break;
        }
    }

    while (mac)
    {
        if(mac->jobID == aux->jobID)
        {
            int value =  concatenateInt(mac->jobID, mac->opID);
            int tu = mac->time;
            for(int i = aux->finalTime+1; i < COL; i++)
            {
                int tuAux = mac->time;
                while(array[mac->id][i] != 0) { i++; }
                while(tuAux != 0)
                {
                    if(array[mac->id][i] == 0)
                    {
                        tuAux--;
                        i++;
                    }
                    else 
                    {
                        i = i - (tu-tuAux);
                        break;
                    }
                } 
                if(tuAux == 0)
                {
                    i -= tu;
                    while (tu != 0)
                    {
                        array[mac->id][i] = value;
                        tu--;
                        i++;
                        if(tu == 0) mac->finalTime = i-1;
                    }
                    break;
                }
            }    
        }
        else
        {
            int value =  concatenateInt(mac->jobID, mac->opID);
            int tu = mac->time;
            for (int i = 1; i < COL; i++)
            {
                int tuAux = mac->time;
                while(array[mac->id][i] != 0) { i++; }
                while(tuAux != 0)
                {
                    if(array[mac->id][i] == 0)
                    {
                        tuAux--;
                        i++;
                    }
                    else 
                    {
                        i = i - (tu-tuAux);
                        break;
                    }
                } 
                if(tuAux == 0)
                {
                    i -= tu;
                    while (tu != 0)
                    {
                        array[mac->id][i] = value;
                        tu--;
                        i++;
                        if(tu == 0) mac->finalTime = i-1;
                    }
                    break;
                } 
            }
        }
        aux = mac;
        mac = mac->next;
    }
       
    char output[10000] = "<table style=\"border-collapse: collapse\"; border=\"1px solid black\">\n<tbody>\n";

    for (int i = 0; i < ROW; i++)
    {
        if (i == 0) strcat(output, "<th>TIME UNITS</th>");
        else
        {
            char id[3];
            sprintf(id, "%d", i);
            strcat(output, "<tr>\n<th>Machine");
            strcat(output, id);
            strcat(output, "</th>\n");
        }
        
        for (int j = 1; j < COL; j++)
        {
            char col[2];
            sprintf(col, "%d", j);
            if(i == 0) 
            {
                strcat(output, "<td>");
                strcat(output, col);
                strcat(output, "</td>\n");
            }
            else
            {
                char pos[5];
                sprintf(pos, "%d", array[i][j]);
                if(array[i][j] != 0) 
                {
                    strcat(output, "<td>");
                    strcat(output, pos);
                    strcat(output, "</td>\n");
                }
                else strcat(output, "<td></td>\n");
            }
        }
        strcat(output, "</tr>\n");
    }

    strcat(output, "</tbody>\n</table>");
    writeHTML("./txt/ProcessPlan.html", output);
}

/**
 * @brief Concatenate 2 integers
 * 
 * @param jobID 
 * @param opID 
 * @return int 
 */
int concatenateInt(int jobID, int opID)
{
    char a[20];
    char b[20];
    sprintf(a, "%d", jobID);
    sprintf(b, "%d", opID);
    strcat(a, b);
    int c = atoi(a);
    return c;
}

/**
 * @brief Write process plan table on html file
 * 
 * @param filename 
 * @param string 
 * @return true 
 * @return false 
 */
bool writeHTML(char* filename, char* string)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) return false;
    else fprintf(file, string);
    fclose(file);
    return true;
}