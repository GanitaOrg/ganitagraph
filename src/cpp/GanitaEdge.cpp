// Ganita edge class

#include "ganita/graph/GanitaEdge.hpp"

GanitaEdge::GanitaEdge()
{
  order_name.push_back("Node-Index");
  order_code = 0;
}

long GanitaEdge::minCheck()
{
  return order_code;
}

