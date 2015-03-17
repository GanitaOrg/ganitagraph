#include "ganita/graph/GanitaGraph.hpp"
//#include "ganita/graph/GanitaNode.hpp"

class GanitaGraphList:public GanitaGraph
{
private:
  uint64_t id;
  uint64_t value;
  int verbosity;
public:
  GanitaGraphList(void);
  GanitaGraphList(int verbosity);
  uint64_t addNew(uint64_t the_id);
  uint64_t dumpList(void);
};

