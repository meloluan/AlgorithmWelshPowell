#ifndef GRAPH_H
#define GRAPH_H

typedef struct doublyLinkedList
{
    struct doublyLinkedList *prev;
    char key;
    struct doublyLinkedList *next;
} list;

typedef struct node
{
    struct node *prev;
    char key;
    list *edge;
    int nEdges;
    struct node *next;
    int color;
} Graph;

void listInsert(list **L, list *x);
list *listSearch(list *L, char k);
void printList(list *L);
list *allocateObject(char k);
Graph *GraphSearch(Graph *L, char k);
void nodeInsert(Graph **G, Graph *x);
Graph *allocateGraph(char k);
void printGraph(Graph *g);
int getNumNodes(Graph *g);
void sort(Graph **start);
void swap(Graph *p1, Graph *p2, Graph **start);
Graph *findmax(Graph *start);
#endif