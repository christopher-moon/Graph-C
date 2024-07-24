//Christopher Moon
//ckmoon
//pa2

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

//def graph
typedef struct GraphObj{

  List *neighbors;
  
  int *color;
  
  int *parents;
  
  int *distance;


  int order;
  
  int edges;
  
  int vertex;

}GraphObj;

//constructor
Graph newGraph(int n){
  
  //allocate for graph
  Graph g = malloc( sizeof(GraphObj) );
  
  if(g){
    
    //allocate for array of lists
    g->neighbors = malloc(sizeof(List*) * (n+1));
    
    for(int i = 0; i < n+1; i++){
      
      //allocate for each list inside the array
      g->neighbors[i] = newList();
    
    }
    
    //allocate for array of colors
    g->color = malloc(sizeof(int*) * (n+1));
    
    //allocate for array of parents
    g->parents = malloc(sizeof(int*) * (n+1));
    
    for(int i = 0; i < n+1; i++){
    
      g->parents[i] = NIL;
    
    }
    
    //allocate for array of distances
    g->distance = malloc(sizeof(int*) * (n+1));
    
    for(int i = 0; i < n+1; i++){
    
      g->distance[i] = INF;
    
    }
    
    //initialize stats
    g->order = n;
    
    g->edges = 0;
    
    g->vertex = NIL;
    
  
  }else{
  
    free(g);
    
    g = NULL;
  
  }
  
  return g;

}

//delete graph
void freeGraph(Graph *pG){
  
  //free array of lists
  for(int i = 0; i < (*pG)->order+1; i++){
      
      //allocate for each list inside the array
      freeList( &(*pG)->neighbors[i] );
    
  }
  
  free((*pG)->neighbors);
  
  (*pG)->neighbors = NULL;
  
  //free int arrays
  free((*pG)->color);
  
  (*pG)->color = NULL;
  
  free((*pG)->parents);
  
  (*pG)->parents = NULL;
  
  free((*pG)->distance);
  
  (*pG)->distance = NULL;
  
  //free entire struct
  free(*pG);
  
  *pG=NULL;

}

//get order
int getOrder(Graph G){

  if( G==NULL ){
  
      printf("error calling on NULL graph reference\n");
      
      exit(1);
  }
  
  return G->order;

}

//get edges
int getSize(Graph G){

  if( G==NULL ){
  
      printf("error calling on NULL graph reference\n");
      
      exit(1);
  }
  
  return G->edges;

}

//get vertex
int getSource(Graph G){

  if( G==NULL ){
  
      printf("error calling on NULL graph reference\n");
      
      exit(1);
  }
  
  return G->vertex;

}

//get parent of u
int getParent(Graph G, int u){

  if( G==NULL ){
  
      printf("error calling on NULL graph reference\n");
      
      exit(1);
  }
  
  if( 1 <= u && u <= getOrder(G)){
  
    return G->parents[u];
  
  }else{
  
    exit(1);
  
  }

}

//get distance 
int getDist(Graph G, int u){

  if( G==NULL ){
  
      printf("error calling on NULL graph reference\n");
      
      exit(1);
  }
  
  if( 1 <= u && u <= getOrder(G)){
  
    return G->distance[u];
  
  }else{
    
    printf("getdist bounds failure\n");
    exit(1);
  
  }

}

//bfs
void BFS(Graph G, int s){

  for(int x = 0; x < getOrder(G)+1; x++){
      
    if(x != s){
    
      //1 = white
      G->color[x] = 1;
      
      G->distance[x] = INF;
      
      G->parents[x] = NIL;
    
    }
    
  }
  
  //2 = gray
  G->color[s] = 2;
  
  G->distance[s] = 0;
  
  G->parents[s] = NIL;
  
  //create empty list
  List l = newList();
  
  //append s to the list
  append(l, s);
  
  int x;
  
  int y;
  
  //while list isnt empty
  while(length(l) > 0){
    
    //get value of front node
    x = front(l);
    
    //delete the front node
    deleteFront(l);
    
    
    //set cursor of vertex x's adjacency list to the first node
    moveFront(G->neighbors[x]);
    
    //loop through nodes in x's list
    for(int i = 0; i < length(G->neighbors[x]); i++){
      
      //get value of y
      y = get(G->neighbors[x]);
      
      //if white
      if(G->color[y] == 1){
      
        G->color[y] = 2;
        
        G->distance[y] = G->distance[x]+1;
        
        G->parents[y] = x;
        
        append(l, y);
      
      }
      
      //move cursor over one
      moveNext(G->neighbors[x]);
    
    }
    
    G->color[x] = 3;
  
  }
  G->vertex = s;
  freeList(&l);
}

//add edge
void addEdge(Graph G, int u, int v){
  
  addArc(G, u, v);
  
  addArc(G, v, u);
  
  G->edges--;

}

//add arc
void addArc(Graph G, int u, int v){

  if( G==NULL ){
  
      printf("error calling on NULL graph reference\n");
      
      exit(1);
  }
  
  //u and v must fall in the required range
  if( (1 <= u && u <= getOrder(G)) && (1 <= v && v <= getOrder(G)) ){
    
    //increase edges by 1
    G->edges++;
    
    //add v to the adjacency list of u
    //if u has nothing in its list, append v
    if(length(G->neighbors[u]) == 0){
      
      append(G->neighbors[u], v);
    
    //else, check if if v is the front element in the list, if so dont do anything cause its already in the list
    }else{
      
        moveFront(G->neighbors[u]);
      
        
        while(index(G->neighbors[u]) > -1 &&  get(G->neighbors[u]) < v ){
        
          moveNext(G->neighbors[u]);
          
          
        }
        
        if(index(G->neighbors[u]) != -1){
        
          insertBefore(G->neighbors[u], v);
        
        }else{
        
          append(G->neighbors[u], v);
        
        }
      
      
      

      
    }
  
  }else{
    
    printf("add arc terminates due to bad u or v value\n");
    exit(1);
  
  }
  
}

void getPath(List L, Graph G, int u){

  if(getSource(G) == NIL){
    
    printf("run BFS before running this function\n");
    exit(1);
  
  }
  
  if( 1 <= u && u <= getOrder(G)){
  
    if(u == getSource(G)){
    
      append(L, getSource(G));
    
    
    }else if(G->parents[u] == NIL){
    
      append(L, NIL);
    
    
    }else{
      
      getPath(L, G, G->parents[u] );
      append(L, u);
      
    }
  
  }else{
  
    exit(1);
  
  }
  
}

//print a graph
void printGraph(FILE* out, Graph G){
  
  int val;
  
  for(int i = 1; i < getOrder(G)+1; i++){
    
    moveFront(G->neighbors[i]);
    fprintf(out, "%d: ", i);
    
    for(int j = 0; j< length(G->neighbors[i]); j++){
      
      val = get(G->neighbors[i]);
      
      fprintf(out, "%d ", val);
      
      moveNext(G->neighbors[i]);
    
    }
    
    //newline
    if(i != getOrder(G)){
    
      fprintf(out, "\n");
    
    }
  
  }

}

void makeNull(Graph G){
  
  int n = getOrder(G);
  
  freeGraph(&G);
  
  G = newGraph(n);

}
