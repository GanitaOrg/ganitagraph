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
  string *property;
public:
  GanitaNode();
  GanitaNode(unsigned long ii, unsigned val, string edgeval);
  unsigned long returnId(void);
  unsigned long returnValue(void);
  string returnProperty(void);
  unsigned long initProperty(string prop);
  unsigned long setId(unsigned long ii);
  unsigned long setValue(unsigned long val);
  unsigned long addEdge(unsigned long val);
  unsigned long addEdge(unsigned long ii, unsigned long val);
  unsigned long setEdge(string edgeval);
  int setEdgeId(unsigned long ee, unsigned long ii);
  int setEdgeValue(unsigned long ee, unsigned long val);
  unsigned long edgestrToMax(string edgeval);
  unsigned long dumpEdgeValues(void);
  unsigned long dumpEdgeAll(void);
  int returnEdge(unsigned long ee, GanitaEdge& ed);
  unsigned long returnNumEdges(void);
};

