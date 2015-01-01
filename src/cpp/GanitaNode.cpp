// Ganita node class.

#include "ganita/graph/GanitaNode.hpp"

GanitaNode::GanitaNode(void)
{
  id = 0;
  value = 0;
}

GanitaNode::GanitaNode(unsigned long ii, unsigned val, string edgeval)
{
  delim = EDGE_STR_DELIM;
  id = ii;
  value = val;
  int jj; jj = 0;
  string token;
  std::istringstream is(edgeval);

  while(std::getline(is, token, delim)) {
    addEdge(stoul(token));
    jj++;
  }
}

unsigned long GanitaNode::returnId(void)
{
  return(id);
}

unsigned long GanitaNode::returnValue(void)
{
  return(value);
}

unsigned long GanitaNode::setId(unsigned long ii)
{
  id = ii;

  return(id);
}

unsigned long GanitaNode::setValue(unsigned long val)
{
  value = val;

  return(value);
}

unsigned long GanitaNode::addEdge(unsigned long val)
{
  GanitaEdge tmpEdge(edge.size() + 1, val);

  edge.push_back(tmpEdge);

  return((unsigned long)edge.size());
}

// Similar to previous function but estimates 
// temporary memory for token. 
unsigned long GanitaNode::setEdge(string edgeval){
  delim = EDGE_STR_DELIM;
  int jj; jj = 0;
  string token;
  std::istringstream is(edgeval);

  while(std::getline(is, token, delim)) {
    addEdge(stoul(token));
    jj++;
  }

  return((unsigned long)edge.size());
}

unsigned long GanitaNode::edgestrToMax(string edgeval)
{
  long double tmp;
  tmp = (long double) edgeval.size() + 1;

  if((size_t) tmp != edgeval.size()){
    fprintf(stderr, "Unable to allocate edges.\n");
    return(0);
  }

  // Add 1 to round up and add another 1 for the comma delimiters in edgeval.
  tmp = ceil(tmp/(log10(tmp) + 1)) + 2;
  
  return((unsigned long) tmp);
}

unsigned long GanitaNode::dumpEdgeValues(void)
{
  if(edge.size() <= 0) return(0);
  unsigned long ii;
  cout<<edge[0].returnValue();
  for(ii=1; ii<(unsigned long)edge.size(); ii++){
    cout<<","<<edge[ii].returnValue();
  }

  return((unsigned long) edge.size());
}

