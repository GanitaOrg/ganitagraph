// Ganita edge class

#include "ganita/graph/GanitaEdge.hpp"

GanitaEdge::GanitaEdge(void)
{
  id = 0;
  value = 0;
}

GanitaEdge::GanitaEdge(unsigned long ii, unsigned long vv)
{
  id = ii;
  value = vv;
}

unsigned long GanitaEdge::returnId(void)
{
  return(id);
}

unsigned long GanitaEdge::returnValue(void)
{
  return(value);
}

unsigned long GanitaEdge::setId(unsigned long ii)
{
  id = ii;
  return(id);
}

unsigned long GanitaEdge::setValue(unsigned long val)
{
  value = val;
  return(value);
}

