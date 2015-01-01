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
  unsigned long id;
  unsigned long value;
  vector<GanitaEdge> edge;
  char delim;
public:
  GanitaNode();
  GanitaNode(unsigned long ii, unsigned val, string edgeval);
  unsigned long returnId(void);
  unsigned long returnValue(void);
  unsigned long setId(unsigned long ii);
  unsigned long setValue(unsigned long val);
  unsigned long addEdge(unsigned long val);
  unsigned long setEdge(string edgeval);
  unsigned long edgestrToMax(string edgeval);
  unsigned long dumpEdgeValues(void);
};

