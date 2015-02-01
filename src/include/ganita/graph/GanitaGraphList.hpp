#include "ganita/graph/GanitaGraph.hpp"
//#include "ganita/graph/GanitaNode.hpp"

class GanitaGraphList:public GanitaGraph
{
private:
  unsigned long id;
  unsigned long value;
  int verbosity;
public:
  GanitaGraphList(void);
  GanitaGraphList(int verbosity);
  unsigned long addNew(unsigned long the_id);
  unsigned long dumpList(void);
};

