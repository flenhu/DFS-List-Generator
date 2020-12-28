
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"

#define INF -1
#define NIL 0
#define UNDEF -1

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G); //number of vertices
int getSize(Graph G); // number of edges
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/*** Manipulation procedures ***/
void makeNull(Graph G);
int insertInList(List l, int v); // helper function for addEdge and addArc
void addEdge(Graph G, int u, int v); // unidirected edge
void addArc(Graph G, int u, int v); // directed edge
void visit(Graph G, List S, int x, int* time);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif