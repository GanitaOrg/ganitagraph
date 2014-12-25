// g++ -O3 ganitaGraph.cc -o ganitaGraph -lm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstring>

using namespace std;

class GanitaGraph
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
  long *gg_rels;
  long *gg_edges;
  double *gg_edge_property;
  //long *gg_edges2;
  long tv, te;
  int compute_edge_flag;
  vector<long> trace[2];
  long kink;
public:
  GanitaGraph();
  int readCSV(ifstream myfile);
  long readCSV(char *myfilestr);
  long readCSV(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long readWeightedEdges(char *mynodefilestr, char *myedgefilestr);
  long getTotalCSV(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long ggInit(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long ggInitWeighted(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long ggAllocRels(long te);
  long ggAllocWeights(long te);
  long ggDeAlloc(long tv);
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

