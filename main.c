#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE_FILE_BUFFER 32

typedef struct
{
    char node1;
    char node2;
} tuple;

void addNodeIfNotExist(char *node, char node1, int numNodes);
int toColor(Graph *g);
void sortArrayDescending(char *arr, size_t size);

int main()
{
    FILE *file;
    char buf[SIZE_FILE_BUFFER];
    int numNodes = 0;
    int numEdges = 0;
    int charsRead = 0;
    Graph *head = NULL;
    Graph *aux = NULL;

    file = fopen("./Graph.txt", "r");
    if (file == NULL)
    {
        printf("Open file error.\n");
        return -1;
    }
    // Get the first line
    if (fgets(buf, SIZE_FILE_BUFFER, file) == NULL)
    {
        printf("Read file error.\n");
        return -1;
    }
    numNodes = atoi(buf);

    // Get the second line
    if (fgets(buf, SIZE_FILE_BUFFER, file) == NULL)
    {
        printf("Read file error.\n");
        return -1;
    }
    numEdges = 2 * atoi(buf);

    printf("Nodes: %d || Edges: %d\n\n", numNodes, numEdges);

    char *nodes = (char *)calloc(numNodes, sizeof(char *));
    tuple *connections = (tuple *)malloc(sizeof(tuple) * numEdges);

    int index = 0;
    while (fgets(buf, SIZE_FILE_BUFFER, file) != NULL)
    {
        printf("%c <-> %c\n", buf[0], buf[2]);
        addNodeIfNotExist(nodes, buf[0], numNodes);
        addNodeIfNotExist(nodes, buf[2], numNodes);
        connections[index].node1 = buf[0];
        connections[index].node2 = buf[2];
        index++;
        // The Graph is not oriented, so we duplicate the edges
        connections[index].node2 = buf[0];
        connections[index].node1 = buf[2];
        index++;
    }

    printf("\n");

    sortArrayDescending(nodes, numNodes);

    for (index = 0; index < numNodes; index++)
    {
        nodeInsert(&head, allocateGraph(nodes[index]));
    }
    for (index = 0; index < numEdges; index++)
    {
        aux = GraphSearch(head, connections[index].node1);
        if (aux == NULL)
        {
            printf("Node not found");
            return -1;
        }
        listInsert(&aux->edge, allocateObject(connections[index].node2));
        aux->nEdges++;
    }
    sort(&head);
    int n = toColor(head);
    printGraph(head);

    printf("\nINFO: The approximate number of colors needed is %d\n", n);

    return 0;
}

void addNodeIfNotExist(char *nodeArr, char node, int numNodes)
{
    int i;
    bool found = false;
    for (i = 0; i < numNodes; i++)
    {
        if (nodeArr[i] == node)
        {
            found = true;
            break;
        }
        if (nodeArr[i] == 0)
        {
            found = false;
            break;
        }
    }
    if (found == false)
    {
        nodeArr[i] = node;
    }
}

int toColor(Graph *g)
{
    int numNodes = getNumNodes(g);
    bool *nodesVisited = (bool *)malloc(sizeof(bool) * numNodes);
    char *nodes = (char *)malloc(sizeof(char) * numNodes);
    int *colors = (int *)malloc(sizeof(int) * numNodes);
    int i = 0;
    int j;
    int color = 0;

    Graph *aux = g;
    while (aux != NULL)
    {
        nodes[i] = aux->key;
        nodesVisited[i] = false;
        colors[i] = -1;
        aux = aux->next;
        i++;
    }
    aux = g;

    i = 0;
    while (aux != NULL)
    {
        if (i >= numNodes)
            break;
        if (colors[i] == -1)
        {
            nodesVisited[i] = true;
            colors[i] = color;
        }
        else
        {
            i++;
            continue;
        }

        list *auxl = aux->edge;
        while (auxl != NULL)
        {
            for (j = 0; j < numNodes; j++)
            {
                if (auxl->key == nodes[j])
                {
                    nodesVisited[j] = true;
                }
            }
            auxl = auxl->next;
        }
        for (j = 0; j < numNodes; j++)
        {
            if (nodesVisited[j] == false)
            {
                if (colors[j] == -1)
                {
                    colors[j] = color;
                    break;
                }
            }
        }
        for (j = 0; j < numNodes; j++)
            nodesVisited[j] = false;

        color++;
        i++;
        aux = aux->next;
    }

    aux = g;
    while (aux != NULL)
    {
        for (j = 0; j < numNodes; j++)
        {
            if (aux->key == nodes[j])
            {
                aux->color = colors[j];
                break;
            }
        }
        aux = aux->next;
    }
    return color;
}

void sortArrayDescending(char *arr, size_t size)
{
    int i, j;
    char a;

    for (i = 0; i < size; ++i)
    {
        for (j = i + 1; j < size; ++j)
        {
            if (arr[i] < arr[j])
            {
                a = arr[i];
                arr[i] = arr[j];
                arr[j] = a;
            }
        }
    }
}
