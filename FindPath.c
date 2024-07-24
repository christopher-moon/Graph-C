//Christopher Moon
//ckmoon
//pa2

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include"List.h"
#include"Graph.h"


int main(int argc, char** argv){
  
  //files
  FILE *infile; 
  FILE *outfile; 
  
  //make sure 2 args
  if(argc != 3){
  
    printf("2 arguments not given\n");
    
    exit(1);
    
  }
  
  //open files
  infile = fopen(argv[1], "r");
  
  outfile = fopen(argv[2], "w");
  
  //check if files are valid
  if(infile==NULL || outfile==NULL){
  
    printf("bad files\n");
    
    exit(1);
    
  }
  
  //get order value, n
  int n;
  
  fscanf(infile, "%d", &n);
  
  //fprintf(outfile, "order is %d\n", n);
  
  //make graph
  Graph g = newGraph(n);
  
  //loop through rest of stuff
  int v1;
  
  int v2;
  
  int phase = 0;
  

  
  while(fscanf(infile, "%d %d", &v1, &v2) != EOF){
    
    if( (v1 != 0 && v2 != 0) && phase == 0){
      
      //add edge to graph struct
      addEdge(g, v1, v2);
    
    }else if(phase == 0){
      
      //printf("end phase 1 and print graph");
      
      
      printGraph(outfile, g);
      phase = 1;
    
    }
    
    if((v1 != 0 && v2 != 0) && phase == 1){
    
      fprintf(outfile, "\n" );
      fprintf(outfile, "\n" );
      
      List l = newList();
      
      //perform bfs with source vertex (v1);
      BFS(g, v1);
      
      if(getDist(g, v2) == INF){
      
        fprintf(outfile, "The distance from %d to %d is infinity\n", v1, v2 );
      
      }else{
      
        fprintf(outfile, "The distance from %d to %d is %d\n", v1, v2, getDist(g, v2) );
      
      }
      
      getPath(l, g, v2);
      
      if(back(l) == NIL){
      
        fprintf(outfile, "No %d-%d path exists\n", v1, v2);
      
      }else{
      
        fprintf(outfile, "A shortest %d-%d path is: ", v1, v2 );
        
        printList(outfile, l);
      
      }
      
      //fprintf(outfile, "A shortest %d-%d path is: ", v1, v2 );
      
      //getPath(l, g, v2);
      
      //printList(outfile, l);
      
      
      freeList(&l);

    
    }
    
    
  
  }
  
  fprintf(outfile, "\n" );
  
  
  freeGraph(&g);
  fclose(infile);
  fclose(outfile);

  return 0;
  
}
