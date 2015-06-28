#ifndef _GANITAGRAPH_
#define _GANITAGRAPH_

#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;

#include "ganita/graph/GanitaNode.hpp"

#ifndef GANITA_GRAPH_MEM_BASE
#define GANITA_GRAPH_MEM_BASE 80
#endif

class GanitaGraph
{
protected:
  vector< std::shared_ptr<GanitaNode> > node;
  uint64_t id;
  uint64_t value;
  int verbosity;
  uint64_t memory_estimate;
public:
  GanitaGraph(void);
  GanitaGraph(int verbose);
  uint64_t set(uint64_t ii, uint64_t val);
  uint64_t returnId(void);
  uint64_t returnValue(void);
  uint64_t addNode1(uint64_t val, string nodeval);
  uint64_t addNode(uint64_t val, string edgeval);
  uint64_t addNode(string edgeval);
  uint64_t returnNumNodes(void);
  GanitaNode *returnNode(uint64_t nn);
  uint64_t computeMemoryEstimate(void);
};

#endif
