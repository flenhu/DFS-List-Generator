
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj{
  List* adj;
  int* color;
  int* parent;
  int* discover;
  int* finish;
  int order; // num of vertices
  int size; // num of edges
}GraphObj;


typedef struct GraphObj* Graph;

Graph newGraph(int n){
    Graph graph = malloc(sizeof(struct GraphObj));
    graph->adj = calloc(n+1, sizeof(List));
    graph->color = calloc(n +1, sizeof(int));
    graph->parent = calloc(n +1, sizeof(int));
    graph->discover = calloc(n +1, sizeof(int));
    graph->finish = calloc(n +1, sizeof(int));
    graph->order = n;
    graph->size = 0;
    for (int i = 1; i <= n; i++) {
        graph->adj[i] = newList();
        graph->color[i] = WHITE; //setting up initial color
        graph->parent[i] = NIL;
        graph->discover[i] = UNDEF; 
        graph->finish[i] = UNDEF;
    }
    return graph;

}

void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL) {
        Graph clr = *pG;
        for(int i =1; i < (clr->order + 1); i++) {
            freeList(&(clr->adj[i]));
        }
        free(clr->adj);
        free(clr->color);
        free(clr->parent);
        free(clr->discover);
        free(clr->finish);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
int getOrder(Graph G){
    if(G == NULL){
        printf("Graph error: cannot getOrder() on NULL Graph reference\n");
        exit(1);
    }
    else{
        return G->order;
    }
}

int getSize(Graph G){
    if(G == NULL){
        printf("Graph error: cannot getSize() on NULL Graph reference\n");
        exit(1);
    }
    else{
        return G->size;
    }
}

int getParent(Graph G, int u){
    if(G == NULL){
        printf("Graph error: cannot getParent() on NULL Graph reference\n");
        exit(1);
    }
    else if( u < 1 || u > getOrder(G)){
        printf("Graph error: cannot getParent() if int u is not within bounds\n");
        exit(1);
    }
    else{
        return G->parent[u];
    }
}

int getDiscover(Graph G, int u){
    if(G == NULL){
        printf("Graph error: cannot getPath() on NULL Graph reference\n");
        exit(1);
    }
    else if( u < 1 || u > getOrder(G)) {
        printf("Graph error: cannot getPath() if u is out of bounds\n");
        exit(1);
    }
    else{
      return G->discover[u];
    }
}


int getFinish(Graph G, int u){/* Pre: 1<=u<=n=getOrder(G) */
    if(G == NULL){
        printf("Graph error: cannot getPath() on NULL Graph reference\n");
        exit(1);
    }
    else if( u < 1 || u > getOrder(G)) {
        printf("Graph error: cannot getPath() if u is out of bounds\n");
        exit(1);
    }
    else{
      return G->finish[u];
    }
}

/*** Manipulation procedures ***************************************/

void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph error: cannot addArc() on NULL Graph reference\n");
        exit(1);
    }
    else if ( u < 1 || v < 1){
        printf("Graph error: cannot addArc() if u or v is below the lower bound\n");
        exit(1);
    }
    else if ( u > getOrder(G) || v > getOrder(G) )  {
        printf("Graph error: cannot addArc() if u or v is above the upper bound\n");
        exit(1);
    }
    else{
        addArc(G, u, v);
        addArc(G, v, u);
        G->size--;
    }

}

void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph error: cannot addArc() on NULL Graph reference\n");
        exit(1);
    }
    else if ( u < 1 || v < 1){
        printf("Graph error: cannot addArc() if u or v is below the lower bound\n");
        exit(1);
    }
    else if ( u > getOrder(G) || v > getOrder(G) )  {
        printf("Graph error: cannot addArc() if u or v is above the upper bound\n");
        exit(1);
    }
    else{
        List L = G->adj[u];
        moveFront(L);
        while(index(L) != -1 && v > get(L)) {
            moveNext(L);
        }
        if(index(L) == -1){
            append(L,v);
            G->size++;
        }
        else{
            insertBefore(L,v);
            G->size++;
        }
    }
}



//algorithm utilized from textbook
void visit(Graph G, List S, int u, int *time){
    if (G == NULL) {
        printf("Graph error: printGraph() called on NULL Graph reference\n");
        exit(1);
    }
    else{
        G->discover[u] = ++*(time);
        G->color[u] = GRAY;
        List L = G->adj[u];
        moveFront(L);
        for(int i = 1; i <= length(L); i++){
            int x = get(L);
            if(G->color[x] == WHITE){
                G->parent[x] = u;
                visit(G, S, x, time);
            }
            moveNext(L);
        }
        G->color[u] = BLACK;
        G->finish[u] = ++*time;
        prepend(S, u);
    }
}

//algorithm utilized from textbook

void DFS(Graph G, List S){
    if (G == NULL) {
        printf("Graph error: printGraph() called on NULL Graph reference\n");
        exit(1);
    }
    else if(length(S) != getOrder(G)){
        printf("Graph error: printGraph() called on NULL Graph reference\n");
        exit(1);
    }
    else{
        int time = 0;
        for(int i = 1; i <= getOrder(G); i++){
            G->color[i] = WHITE;
            G->parent[i] = NIL;
        }
        moveFront(S);
        for(int i = 1; i <= getOrder(G); i++){
            int x = get(S);
            moveNext(S);
            if(G->color[x] == WHITE){
                visit(G, S, x, &time);
            }
        }
        for(int i = 1; i <= getOrder(G); i++ ){
            deleteBack(S);
        }
    }
}


/*** Other operations *****************************************************/
Graph transpose(Graph G){
    if (G == NULL) {
        printf("Graph error: printGraph() called on NULL Graph reference\n");
        exit(1);
    }
    else{
        Graph trans = newGraph(G->order);
        for(int i = 1; i <= G->order; i++){
            List L = G->adj[i];
            moveFront(L);
            while(index(L) >= 0){
                addArc(trans, get(L), i);
                moveNext(L);
            }
        }
        return trans;
    }
}

Graph copyGraph(Graph G){
    if (G == NULL) {
        printf("Graph error: printGraph() called on NULL Graph reference\n");
        exit(1);
    }
    else{
        Graph carbon = newGraph(G->order);
        for(int i =1; i <= G->order; i++){
            List L = G->adj[i];
            moveFront(L);
            while(index(L) != -1){
                append(carbon->adj[i], get(L) );
                moveNext(L);
            }
        }
        return carbon;
    } 
}

void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        printf("Graph error: printGraph() called on NULL Graph reference\n");
        exit(1);
    }
    else {
        for(int i = 1; i <= getOrder(G); i++){
            fprintf(out, "%d: ", i);
            printList(out, G->adj[i]);
            fprintf(out, "\n");
        }
    }
}