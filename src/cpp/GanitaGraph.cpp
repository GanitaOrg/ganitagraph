#include "ganita/graph/GanitaGraph.hpp"

GanitaGraph::GanitaGraph(void)
{
  id = 0;
  value = 0;
  memory_estimate = GANITA_GRAPH_MEM_BASE;
}

GanitaGraph::GanitaGraph(int verbose)
{
  id = 0;
  value = 0;
  verbosity = verbose;
  memory_estimate = GANITA_GRAPH_MEM_BASE;
}

unsigned long GanitaGraph::set(unsigned long ii, unsigned long val)
{
  id = ii;
  value = val;

  return(id);
}

unsigned long GanitaGraph::returnId(void)
{
  return(id);
}

unsigned long GanitaGraph::returnValue(void)
{
  return(value);
}

unsigned long GanitaGraph::addNode(unsigned long val, string edgeval)
{
  GanitaNode *tmpNode = new GanitaNode();

  tmpNode->setId((unsigned long)node.size() + 1);
  tmpNode->setValue(val);
  tmpNode->setEdge(edgeval);

  node.push_back(std::make_shared<GanitaNode>(*tmpNode));
  delete tmpNode;

  return((unsigned long)node.size());
}

unsigned long GanitaGraph::addNode(string edgeval)
{
  GanitaNode *tmpNode = new GanitaNode();

  tmpNode->setId((unsigned long)node.size() + 1);
  tmpNode->setValue((unsigned long)node.size() + 1);
  tmpNode->setEdge(edgeval);

  node.push_back(std::make_shared<GanitaNode>(*tmpNode));
  delete tmpNode;

  return((unsigned long)node.size());
}

unsigned long GanitaGraph::returnNumNodes(void)
{
  return(node.size());
}

GanitaNode *GanitaGraph::returnNode(unsigned long nn)
{
  if(node.size() <= 0){
    // no nodes added yet
    return(NULL);
  }

  return(node[nn % node.size()].get());
}

unsigned long GanitaGraph::computeMemoryEstimate(void)
{
  unsigned long ii;

  memory_estimate = GANITA_GRAPH_MEM_BASE;

  for(ii=0; ii<node.size(); ii++){
    memory_estimate += sizeof(GanitaNode) + 
      (node[ii]->returnNumEdges())*sizeof(GanitaEdge);
  }

  return(memory_estimate);
}

