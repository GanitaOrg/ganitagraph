#include <cstdint>
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
  uint64_t setId(uint64_t ii);
  uint64_t setValue(uint64_t val);
  uint64_t returnId(void);
  uint64_t returnValue(void);
  uint64_t addNew(uint64_t the_id);
  uint64_t buildMaxList(uint64_t the_id, uint64_t nv, uint64_t listsize);
  uint64_t dumpList(void);
  uint64_t dumpList2(void);
};

