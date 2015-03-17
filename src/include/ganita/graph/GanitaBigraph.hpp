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
  int64_t total;
  vector<string> nodes1;
  vector<string> nodes2;
  vector<int64_t> counts1;
  vector<int64_t> counts2;
  vector<int64_t> ti;
  vector<int64_t> ti2;
  vector<int64_t> si;
  string node_csv;
  string rel_csv;
  // Initially edges can be loaded into gg_rels. 
  // gg_rels stores edges as a single array 
  // with even indices pointing to the originating node 
  // and odd indices pointing to the destination node. 
  int64_t *gg_rels;
  // gg_edges re-organizes the edges. 
  // All edges are packed into a single array. 
  // It is ordered according to source node and then 
  // the destination nodes for each source node. 
  int64_t *gg_edges;
  double *gg_edge_property;
  //int64_t *gg_edges2;
  // tv is the total number of vertices or nodes. 
  // te is the total number of edges. 
  int64_t tv, te;
  int compute_edge_flag;
  vector<int64_t> trace[2];
  int64_t kink;
public:
  GanitaBigraph();
  int readCSV(ifstream myfile);
  int64_t readCSV(char *myfilestr);
  int64_t readCSV(char *myfilestr,char *myfilestr2,char *myfilestr3);
  int64_t readWeightedEdges(char *mynodefilestr, char *myedgefilestr);
  int64_t getTotalCSV(char *myfilestr,char *myfilestr2,char *myfilestr3);
  int64_t ggInit(char *myfilestr,char *myfilestr2,char *myfilestr3);
  int64_t ggInitWeighted(char *myfilestr,char *myfilestr2,char *myfilestr3);
  int64_t ggAllocRels(int64_t te);
  int64_t ggAllocWeights(int64_t te);
  int64_t ggDeAlloc(void);
  int64_t createEdges(char *myfilestr);
  int64_t createWeightedEdges(char *myfilestr);
  int64_t dumpIndices();
  int64_t computeEdges();
  int64_t dumpEdges();
  int64_t dumpRels();
  int64_t setMinTrace(int64_t len);
  int64_t recommenderBasic(int64_t ncom, int64_t check_4_cycle);
  int64_t checkCycle4(int64_t ncom);
  int64_t nodeDotProd(int64_t nn1, int64_t nn2);
  int64_t nodeDotProd(int64_t nn1);
  int64_t nodeDotProd2(int64_t nn1, int64_t nn2, int64_t tt);
  int64_t nodeDotProd2(int64_t nn1, int64_t tt);
  int64_t returnNumNodes();
};

