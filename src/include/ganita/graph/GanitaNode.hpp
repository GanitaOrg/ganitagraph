// g++ -O3 GanitaNode.c -o GanitaNode -lm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <sstream>

#ifndef EDGE_STR_DELIM
#define EDGE_STR_DELIM ','
#endif

#ifndef MAX_TMP_ALLOC
#define MAX_TMP_ALLOC 128000000
#endif

using namespace std;

#include "ganita/graph/GanitaEdge.hpp"

class GanitaNode
{
private:
  uint64_t id;
  uint64_t value;
  vector<GanitaEdge> edge;
  char delim;
  string *property;
public:
  GanitaNode();
  GanitaNode(uint64_t ii, unsigned val, string edgeval);
  uint64_t returnId(void);
  uint64_t returnValue(void);
  string returnProperty(void);
  uint64_t initProperty(string prop);
  uint64_t setId(uint64_t ii);
  uint64_t setValue(uint64_t val);
  uint64_t addEdge(uint64_t val);
  uint64_t addEdge(uint64_t ii, uint64_t val);
  uint64_t setEdge(string edgeval);
  int setEdgeId(uint64_t ee, uint64_t ii);
  int setEdgeValue(uint64_t ee, uint64_t val);
  uint64_t edgestrToMax(string edgeval);
  uint64_t dumpEdgeValues(void);
  uint64_t dumpEdgeAll(void);
  int returnEdge(uint64_t ee, GanitaEdge& ed);
  uint64_t returnNumEdges(void);
};

