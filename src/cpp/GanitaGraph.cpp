#include "ganita/graph/GanitaGraph.hpp"

GanitaGraph::GanitaGraph(void)
{
  id = 0;
  value = 0;
}

unsigned long GanitaGraph::returnId(void)
{
  return(id);
}

unsigned long GanitaGraph::returnValue(void)
{
  return(value);
}

