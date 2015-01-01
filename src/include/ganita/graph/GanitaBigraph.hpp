// g++ -O3 ganitaGraph.cc -o ganitaGraph -lm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

#include "ganita/graph/GanitaGraph.hpp"

class GanitaBigraph:public GanitaGraph
{
private:
  long total;
  vector<string> nodes1;
  vector<string> nodes2;
  vector<long> counts1;
  vector<long> counts2;
  vector<long> ti;
  vector<long> ti2;
  vector<long> si;
  string node_csv;
  string rel_csv;
  // Initially edges can be loaded into gg_rels. 
  // gg_rels stores edges as a single array 
  // with even indices pointing to the originating node 
  // and odd indices pointing to the destination node. 
  long *gg_rels;
  // gg_edges re-organizes the edges. 
  // All edges are packed into a single array. 
  // It is ordered according to source node and then 
  // the destination nodes for each source node. 
  long *gg_edges;
  double *gg_edge_property;
  //long *gg_edges2;
  // tv is the total number of vertices or nodes. 
  // te is the total number of edges. 
  long tv, te;
  int compute_edge_flag;
  vector<long> trace[2];
  long kink;
public:
  GanitaBigraph();
  int readCSV(ifstream myfile);
  long readCSV(char *myfilestr);
  long readCSV(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long readWeightedEdges(char *mynodefilestr, char *myedgefilestr);
  long getTotalCSV(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long ggInit(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long ggInitWeighted(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long ggAllocRels(long te);
  long ggAllocWeights(long te);
  long ggDeAlloc(void);
  long createEdges(char *myfilestr);
  long createWeightedEdges(char *myfilestr);
  long dumpIndices();
  long computeEdges();
  long dumpEdges();
  long dumpRels();
  long setMinTrace(long len);
  long recommenderBasic(long ncom, long check_4_cycle);
  long checkCycle4(long ncom);
  long nodeDotProd(long nn1, long nn2);
  long nodeDotProd(long nn1);
  long nodeDotProd2(long nn1, long nn2, long tt);
  long nodeDotProd2(long nn1, long tt);
  long returnNumNodes();
};

