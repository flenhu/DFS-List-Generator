
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
	int i, n=8;
	List S = newList();
	Graph G = newGraph(n);
	Graph T=NULL;

   for(i=1; i<=n; i++){
   	append(S, i);
   }

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);

   printGraph(stdout, A);
   printf("\n");
   printf("Order: %d\n", getOrder(A));
   printf("Size     : %d\n", getSize(A));


   printf("Running DFS Algorithm");
   DFS(A, S);
   printlist(stdout, S);
   printf("Vertexes");
   printf("Vertex 1:\t%d\t%d\t%d\n", getDiscover(A, 1), getFinish(A, 1), getParent(A, 1));
   printf("Vertex 2:\t%d\t%d\t%d\n", getDiscover(A, 2), getFinish(A, 2), getParent(A, 2));
   printf("Vertex 3:\t%d\t%d\t%d\n", getDiscover(A, 3), getFinish(A, 3), getParent(A, 3));
   printf("Vertex 4:\t%d\t%d\t%d\n", getDiscover(A, 4), getFinish(A, 4), getParent(A, 4));
   printf("Vertex 5:\t%d\t%d\t%d\n", getDiscover(A, 5), getFinish(A, 5), getParent(A, 5));
   printf("Vertex 6:\t%d\t%d\t%d\n", getDiscover(A, 6), getFinish(A, 6), getParent(A, 6));
   printf("Vertex 7:\t%d\t%d\t%d\n", getDiscover(A, 7), getFinish(A, 7), getParent(A, 7));
   printf("Vertex 8:\t%d\t%d\t%d\n", getDiscover(A, 8), getFinish(A, 8), getParent(A, 8));

   T = transpose(A);

   printf("Printing tranpose\n", );
   printGraph(stdout, T);
   printf("Order: %d\n", getOrder(T));
   printf("Size     : %d\n", getSize(T));



}