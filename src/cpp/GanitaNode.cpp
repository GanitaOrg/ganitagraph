// Ganita node class.

#include "ganita/graph/GanitaNode.hpp"

GanitaNode::GanitaNode(void)
{
  id = 0;
  value = 0;
}

GanitaNode::GanitaNode(uint64_t ii, unsigned val, string edgeval)
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

uint64_t GanitaNode::returnId(void)
{
  return(id);
}

uint64_t GanitaNode::returnValue(void)
{
  return(value);
}

string GanitaNode::returnProperty(void)
{
  return(*property);
}

uint64_t GanitaNode::initProperty(string prop)
{
  property = new string(prop);
  return(property->size());
}

uint64_t GanitaNode::setId(uint64_t ii)
{
  id = ii;

  return(id);
}

uint64_t GanitaNode::setValue(uint64_t val)
{
  value = val;

  return(value);
}

uint64_t GanitaNode::addEdge(uint64_t val)
{
  GanitaEdge tmpEdge(edge.size() + 1, val);

  edge.push_back(tmpEdge);

  return((uint64_t)edge.size());
}

uint64_t GanitaNode::addEdge(uint64_t ii, uint64_t val)
{
  GanitaEdge tmpEdge(ii, val);

  edge.push_back(tmpEdge);

  return((uint64_t)edge.size());
}

// Similar to previous function but estimates 
// temporary memory for token. 
uint64_t GanitaNode::setEdge(string edgeval){
  delim = EDGE_STR_DELIM;
  int jj; jj = 0;
  string token;
  std::istringstream is(edgeval);

  while(std::getline(is, token, delim)) {
    addEdge(stoul(token));
    jj++;
  }

  return((uint64_t)edge.size());
}

uint64_t GanitaNode::edgestrToMax(string edgeval)
{
  double tmp;
  tmp = (double) edgeval.size() + 1;

  if((size_t) tmp != edgeval.size()){
    fprintf(stderr, "Unable to allocate edges.\n");
    return(0);
  }

  // Add 1 to round up and add another 1 for the comma delimiters in edgeval.
  tmp = ceil(tmp/(log10(tmp) + 1)) + 2;
  
  return((uint64_t) tmp);
}

uint64_t GanitaNode::dumpEdgeValues(void)
{
  if(edge.size() <= 0) return(0);
  uint64_t ii;
  cout<<edge[0].returnValue();
  for(ii=1; ii<(uint64_t)edge.size(); ii++){
    cout<<","<<edge[ii].returnValue();
  }

  return((uint64_t) edge.size());
}

uint64_t GanitaNode::dumpEdgeAll(void)
{
  if(edge.size() <= 0) return(0);
  uint64_t ii;
  cout<<edge[0].returnId()<<","<<edge[0].returnValue();
  for(ii=1; ii<(uint64_t)edge.size(); ii++){
    cout<<"|"<<edge[ii].returnId()<<","<<edge[ii].returnValue();
  }
  cout<<endl;

  return((uint64_t) edge.size());
}

int GanitaNode::returnEdge(uint64_t ee, GanitaEdge& ed)
{
  if(edge.size() > 0){
    ed = edge[ee % edge.size()];
    return(1);
  }
  return(0);
}

int GanitaNode::setEdgeId(uint64_t ee, uint64_t ii)
{
  if(edge.size() > 0){
    edge[ee % edge.size()].setId(ii);
    return(1);
  }
  return(0);
}

int GanitaNode::setEdgeValue(uint64_t ee, uint64_t val)
{
  if(edge.size() > 0){
    edge[ee % edge.size()].setValue(val);
    return(1);
  }
  return(0);
}

uint64_t GanitaNode::returnNumEdges(void)
{
  return(edge.size());
}

