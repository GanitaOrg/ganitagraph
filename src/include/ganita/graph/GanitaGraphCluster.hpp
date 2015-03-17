#include <vector>
#include "ganita/graph/GanitaGraph.hpp"
//#include "ganita/graph/GanitaNode.hpp"

class GanitaGraphCluster:public GanitaGraph
{
private:
  uint64_t id;
  uint64_t value;
  uint64_t num_modes;      // number of desired modes
  vector<uint64_t> modes;  // list of node indices that are modes
public:
  GanitaGraphCluster(void);
  GanitaGraphCluster(uint64_t nm);
  uint64_t addNew(string prop);
  uint64_t dumpList(void);
  int subtract(char b1, char b2);
};

