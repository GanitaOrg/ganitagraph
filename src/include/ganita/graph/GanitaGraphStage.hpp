#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;

#include "ganita/graph/GanitaGraph.hpp"
#include "ganita/graph/GanitaNode.hpp"

class GanitaGraphStage:public GanitaGraph
{
private:
  vector< std::shared_ptr<GanitaNode> > stagenode;
  unsigned long id;
  unsigned long value;
  int verbosity;
public:
  GanitaGraphStage(void);
  GanitaGraphStage(int verbose);
  unsigned long set(unsigned long ii, unsigned long val);
  unsigned long returnId(void);
  unsigned long returnValue(void);
  unsigned long addNode(unsigned long val, string edgeval);
  unsigned long addNode(string edgeval);
  unsigned long returnNumNodes(void);
  GanitaNode *returnNode(unsigned long nn);
};

