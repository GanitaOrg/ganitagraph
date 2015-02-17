#include <vector>
#include "ganita/graph/GanitaGraph.hpp"
//#include "ganita/graph/GanitaNode.hpp"

class GanitaGraphCluster:public GanitaGraph
{
private:
  unsigned long id;
  unsigned long value;
  unsigned long num_modes;      // number of desired modes
  vector<unsigned long> modes;  // list of node indices that are modes
public:
  GanitaGraphCluster(void);
  GanitaGraphCluster(unsigned long nm);
  unsigned long addNew(string prop);
  unsigned long dumpList(void);
  int subtract(char b1, char b2);
};

