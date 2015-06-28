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

uint64_t GanitaGraph::set(uint64_t ii, uint64_t val)
{
  id = ii;
  value = val;

  return(id);
}

uint64_t GanitaGraph::returnId(void)
{
  return(id);
}

uint64_t GanitaGraph::returnValue(void)
{
  return(value);
}

uint64_t GanitaGraph::addNode1(uint64_t val, string nodeval)
{
  GanitaNode *tmpNode = new GanitaNode();

  tmpNode->setId((uint64_t)node.size() + 1);
  tmpNode->setValue(val);
  tmpNode->initProperty(nodeval);

  node.push_back(std::make_shared<GanitaNode>(*tmpNode));
  delete tmpNode;

  return((uint64_t)node.size());
}

uint64_t GanitaGraph::addNode(uint64_t val, string edgeval)
{
  GanitaNode *tmpNode = new GanitaNode();

  tmpNode->setId((uint64_t)node.size() + 1);
  tmpNode->setValue(val);
  tmpNode->setEdge(edgeval);

  node.push_back(std::make_shared<GanitaNode>(*tmpNode));
  delete tmpNode;

  return((uint64_t)node.size());
}

uint64_t GanitaGraph::addNode(string edgeval)
{
  GanitaNode *tmpNode = new GanitaNode();

  tmpNode->setId((uint64_t)node.size() + 1);
  tmpNode->setValue((uint64_t)node.size() + 1);
  tmpNode->setEdge(edgeval);

  node.push_back(std::make_shared<GanitaNode>(*tmpNode));
  delete tmpNode;

  return((uint64_t)node.size());
}

uint64_t GanitaGraph::returnNumNodes(void)
{
  return(node.size());
}

GanitaNode *GanitaGraph::returnNode(uint64_t nn)
{
  if(node.size() <= 0){
    // no nodes added yet
    return(NULL);
  }

  return(node[nn % node.size()].get());
}

uint64_t GanitaGraph::computeMemoryEstimate(void)
{
  uint64_t ii;

  memory_estimate = GANITA_GRAPH_MEM_BASE;

  for(ii=0; ii<node.size(); ii++){
    memory_estimate += sizeof(GanitaNode) + 
      (node[ii]->returnNumEdges())*sizeof(GanitaEdge);
  }

  return(memory_estimate);
}

