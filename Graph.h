//Christopher Moon
//ckmoon
//pa2

#ifndef __GRAPH_H__
#define __GRAPH_H__

#define INF -2
#define NIL -1

#include "List.h"

typedef struct GraphObj* Graph;

//typedef struct ListObj* List;

Graph newGraph(int n);

void freeGraph(Graph *pG);

int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void BFS(Graph G, int s);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void getPath(List L, Graph G, int u);

void printGraph(FILE* out, Graph G);

void makeNull(Graph G);

#endif
