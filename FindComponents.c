
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
  Graph G = NULL;
  int order, scc =0; //num of vertices
  int count = 1;
  int v1, v2;

  if(argc != 3){
    printf("Usage: <input file> <output file>\n");
    exit(1);
  }

  FILE *in, *out;
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  if( in == NULL){
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  else if(out == NULL){
    printf("Unable to open file %s for writing\n",argv[2]);
    exit(1);
  }
  else{
    fscanf(in, "%d", &order);
    Graph G = newGraph(order);
    //making of graph
    while(fgetc(in) != EOF){
      fscanf(in, "%d %d", &v1, &v2); 
      if (v1 == 0 && v2 == 0) {
        break;
      }
      else{
        addArc(G, v1, v2);
      }
    }

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    //provided algorithm from lecture
    List L = newList();
    for(int i =1; i <= order; i++){
      append(L,i);
    }
    DFS(G,L);
    Graph tran = transpose(G);
    DFS(tran, L);

    //counting stronly connected components
    for(int i = 1; i < getOrder(G) + 1; i++){
      if(getParent(tran,i) == NIL)
        scc++;
    }

    fprintf(out, "\nG contains %d strongly connected components:\n", scc);

    //popping items off stack
    List S = newList();
    moveBack(L);

    while(index(L) != -1){
      prepend(S, get(L));
      if(getParent(tran, get(L)) == NIL){
        fprintf(out, "Component %d: ", count);
        printList(out, S);
        fprintf(out,"\n");
        clear(S);
        count++;
      }
          movePrev(L);
  }

  freeGraph(&tran);
  freeList(&L);
  freeList(&S);

  }
  freeGraph(&G);


  fclose(in);
  fclose(out);
}