// Ganita trace class.

#include "ganita/graph/GanitaTrace.hpp"

GanitaTrace::GanitaTrace()
{
  //order_name.push_back("Node-Index");
  //order_code = 0;
  kink = 0;
}

int64_t GanitaTrace::findKink()
{
  return kink;
}
