#include <vector>
//#include <boost/shared_ptr.hpp>
#include <memory>

using namespace std;

#include "ganita/graph/GanitaGraph.hpp"
#include "ganita/graph/GanitaNode.hpp"

class GanitaGraphStage:public GanitaGraph
{
private:
  vector< std::shared_ptr<GanitaNode> > stagenode;
  uint64_t id;
  uint64_t value;
  int verbosity;
public:
  GanitaGraphStage(void);
  GanitaGraphStage(int verbose);
  uint64_t set(uint64_t ii, uint64_t val);
  uint64_t returnId(void);
  uint64_t returnValue(void);
  uint64_t addNode(uint64_t val, string edgeval);
  uint64_t addNode(string edgeval);
  uint64_t returnNumNodes(void);
  GanitaNode *returnNode(uint64_t nn);
};

