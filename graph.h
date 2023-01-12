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
    struct node *next;
    int color;
} graph;

void listInsert(list **L, list *x);
list *listSearch(list *L, char k);
void printList(list *L);
list *allocateObject(char k);
graph *graphSearch(graph *L, char k);
void nodeInsert(graph **G, graph *x);
graph *allocateGraph(char k);
void printGraph(graph *g);
int getNumNodes(graph *g);

#endif