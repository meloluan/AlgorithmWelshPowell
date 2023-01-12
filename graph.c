#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void listInsert(list **L, list *x)
{
    x->next = *L;
    if (*L != NULL)
        (*L)->prev = x;
    *L = x;
    x->prev = NULL;
}

void printList(list *L)
{
    list *x = L;
    while (x != NULL)
    {
        printf("%c", x->key);
        x = x->next;
        if (x != NULL)
            printf(" -> ");
    }
    printf("\n");
}

list *allocateObject(char k)
{
    list *x = (list *)malloc(sizeof(struct doublyLinkedList));
    x->key = k;
    x->next = NULL;
    x->prev = NULL;
    return x;
}

graph *graphSearch(graph *L, char k)
{
    graph *x = L;
    while (x != NULL && x->key != k)
        x = x->next;
    return x;
}

void nodeInsert(graph **G, graph *x)
{
    x->next = *G;
    if (*G != NULL)
        (*G)->prev = x;
    *G = x;
    x->prev = NULL;
}

graph *allocateGraph(char k)
{
    graph *x = (graph *)malloc(sizeof(struct node));
    x->key = k;
    x->edge = NULL;
    x->next = NULL;
    x->prev = NULL;
    x->color = -1;
    return x;
}

void printGraph(graph *g)
{
    graph *auxg = g;
    while (auxg != NULL)
    {
        printf("Node: %c | Color: %d\n\t\t edge: ", auxg->key, auxg->color);

        list *auxl = auxg->edge;
        printList(auxl);
        auxg = auxg->next;
    }
}

int getNumNodes(graph *g)
{
    int count = 0;
    while (g != NULL)
    {
        count++;
        g = g->next;
    }
    return count;
}