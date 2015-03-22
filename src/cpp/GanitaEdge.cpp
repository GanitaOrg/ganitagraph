// Ganita edge class

#include "ganita/graph/GanitaEdge.hpp"

GanitaEdge::GanitaEdge(void)
{
  id = 0;
  value = 0;
}

GanitaEdge::GanitaEdge(uint64_t ii, uint64_t vv)
{
  id = ii;
  value = vv;
}

uint64_t GanitaEdge::returnId(void)
{
  return(id);
}

uint64_t GanitaEdge::returnValue(void)
{
  return(value);
}

uint64_t GanitaEdge::setId(uint64_t ii)
{
  id = ii;
  return(id);
}

uint64_t GanitaEdge::setValue(uint64_t val)
{
  value = val;
  return(value);
}

