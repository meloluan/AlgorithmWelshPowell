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

Graph *GraphSearch(Graph *L, char k)
{
    Graph *x = L;
    while (x != NULL && x->key != k)
        x = x->next;
    return x;
}

void nodeInsert(Graph **G, Graph *x)
{
    x->next = *G;
    if (*G != NULL)
        (*G)->prev = x;
    *G = x;
    x->prev = NULL;
}

Graph *allocateGraph(char k)
{
    Graph *x = (Graph *)malloc(sizeof(struct node));
    x->key = k;
    x->edge = NULL;
    x->next = NULL;
    x->prev = NULL;
    x->color = -1;
    x->nEdges = 0;
    return x;
}

void printGraph(Graph *g)
{
    Graph *auxg = g;
    while (auxg != NULL)
    {
        printf("Node: %c | Color: %d | Num Edges: %d | Edges: ", auxg->key, auxg->color, auxg->nEdges);

        list *auxl = auxg->edge;
        printList(auxl);
        auxg = auxg->next;
    }
}

int getNumNodes(Graph *g)
{
    int count = 0;
    while (g != NULL)
    {
        count++;
        g = g->next;
    }
    return count;
}

void sort(Graph **start)
{
    if (((*start)->next == NULL) || (*start == NULL))
    {
        return;
    }
    Graph *max = findmax(*start);
    if (max == NULL)
        return;
    swap(*start, max, start);
    sort(&((*start)->next));
}

void swap(Graph *p1, Graph *p2, Graph **start)
{
    Graph *p1pre = NULL;
    Graph *p1curr = *start;
    while (p1curr != p1)
    {
        p1pre = p1curr;
        p1curr = p1curr->next;
    }
    Graph *p2pre = NULL;
    Graph *p2curr = *start;
    while (p2curr != p2)
    {
        p2pre = p2curr;
        p2curr = p2curr->next;
    }
    if (p1pre != NULL)
    {
        p1pre->next = p2curr;
    }
    else
    {
        *start = p2curr;
    }
    if (p2pre != NULL)
    {
        p2pre->next = p1curr;
    }
    else
    {
        *start = p1curr;
    }
    Graph *temp = p2curr->next;
    p2curr->next = p1curr->next;
    p1curr->next = temp;
}

Graph *findmax(Graph *start)
{
    int flag = 0;
    if (start != NULL)
    {
        Graph *curr = start->next;
        Graph *max = start;
        while (curr->next != NULL)
        {
            if (max->nEdges < curr->nEdges)
            {
                max = curr;
                flag++;
            }
            curr = curr->next;
        }
        if ((curr->next == NULL) && (max->nEdges < curr->nEdges))
        {
            max = curr;
            flag++;
        }
        if (flag > 0)
        {
            return max;
        }
    }
    return start;
}