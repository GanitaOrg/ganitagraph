// This class is used to buffer graph data on disk. 

#ifndef _GANITAGRAPHFILE_
#define _GANITAGRAPHFILE_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include "ganita/graph/GanitaGraph.hpp"

//default buffer size (1M)
#ifndef GANITA_DEFAULT_GRAPH_BUFFER_SIZE
#define GANITA_DEFAULT_GRAPH_BUFFER_SIZE 1000000
#endif

using namespace std;

class GanitaGraphFile
{
private:
  std::fstream gg_graph_file;
  char file_name[500];
  uint64_t gg_buf_size;
  uint64_t gg_fixed_buf_size;
  uint64_t gg_buffer_num;
  uint64_t gg_buf_start;
  uint64_t gg_file_size;
public:
  GanitaGraphFile();
  uint64_t openGraphFile(char buf_file[]);
  uint64_t createGraphFile(void);
  int writeGraphHeader(GanitaGraph *mygg);
  int writeGraph(GanitaGraph *mygg);
  int writeGraphNode(GanitaNode *mygn);
  int writeGraphNodeEdges(GanitaNode *mygn);
  int writeGraphEdge(GanitaEdge *myge);
  int close(void);
  int writeVisTables(GanitaGraph *ga);
};

#endif
