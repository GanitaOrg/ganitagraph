#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;

#include "ganita/graph/GanitaNode.hpp"

class GanitaGraph
{
protected:
  vector< std::shared_ptr<GanitaNode> > node;
  unsigned long id;
  unsigned long value;
  int verbosity;
public:
  GanitaGraph(void);
  GanitaGraph(int verbose);
  unsigned long set(unsigned long ii, unsigned long val);
  unsigned long returnId(void);
  unsigned long returnValue(void);
  unsigned long addNode(unsigned long val, string edgeval);
  unsigned long addNode(string edgeval);
  unsigned long returnNumNodes(void);
  GanitaNode *returnNode(unsigned long nn);
};

