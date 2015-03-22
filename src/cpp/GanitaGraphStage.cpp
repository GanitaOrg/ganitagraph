#include "ganita/graph/GanitaGraphStage.hpp"

GanitaGraphStage::GanitaGraphStage(void)
{
  id = 0;
  value = 0;
}

GanitaGraphStage::GanitaGraphStage(int verbose)
{
  id = 0;
  value = 0;
  verbosity = verbose;
}

uint64_t GanitaGraphStage::set(uint64_t ii, uint64_t val)
{
  id = ii;
  value = val;

  return(id);
}

uint64_t GanitaGraphStage::returnId(void)
{
  return(id);
}

uint64_t GanitaGraphStage::returnValue(void)
{
  return(value);
}

uint64_t GanitaGraphStage::addNode(uint64_t val, string edgeval)
{
  GanitaNode *tmpNode = new GanitaNode();

  tmpNode->setId((uint64_t)stagenode.size() + 1);
  tmpNode->setValue(val);
  tmpNode->setEdge(edgeval);

  stagenode.push_back(std::make_shared<GanitaNode>(*tmpNode));
  delete tmpNode;

  return((uint64_t)stagenode.size());
}

uint64_t GanitaGraphStage::addNode(string edgeval)
{
  GanitaNode *tmpNode = new GanitaNode();

  tmpNode->setId((uint64_t)stagenode.size() + 1);
  tmpNode->setValue((uint64_t)stagenode.size() + 1);
  tmpNode->setEdge(edgeval);

  stagenode.push_back(std::make_shared<GanitaNode>(*tmpNode));
  delete tmpNode;

  return((uint64_t)stagenode.size());
}

uint64_t GanitaGraphStage::returnNumNodes(void)
{
  return(stagenode.size());
}

GanitaNode *GanitaGraphStage::returnNode(uint64_t nn)
{
  if(stagenode.size() <= 0){
    // no nodes added yet
    return(NULL);
  }

  return(stagenode[nn % stagenode.size()].get());
}

