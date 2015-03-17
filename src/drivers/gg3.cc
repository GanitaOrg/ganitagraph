// g++ -std=c++11 -O3 gg2.cc -o gg2 -lm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <math.h>

#include "ganita/graph/GanitaGraphList.hpp"

int main(int argc, char *argv[])
{
  GanitaGraphList gg;

  // if(argc < 3){
  //   cout<<"Usage: node-file edge-file"<<endl;;
  //   exit(1);
  // }

  //gg.ggInit(argv[1],argv[2],argv[3]);

  if(argc > 1){
    cout<<"Command line argument "<<argv[1]<<endl;
  }

  gg.addNew(1);
  gg.addNew(25);
  gg.addNew(21);
  gg.addNew(8);
  gg.addNew(21);
  gg.addNew(17);
  gg.dumpList();
  cout<<"\nReached end"<<endl;
  
  cout<<"Size of GanitaNode: "<<sizeof(GanitaNode)<<endl;
  cout<<"Size of GanitaEdge: "<<sizeof(GanitaEdge)<<endl;
  cout<<"Size of GanitaGraph: "<<sizeof(GanitaGraph)<<endl;
  cout<<"Size of GanitaGraphList: "<<sizeof(GanitaGraphList)<<endl;

  cout<<"Memory estimate: "<<gg.computeMemoryEstimate()<<endl;

  exit(1);
}

