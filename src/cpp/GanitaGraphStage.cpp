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

unsigned long GanitaGraphStage::set(unsigned long ii, unsigned long val)
{
  id = ii;
  value = val;

  return(id);
}

unsigned long GanitaGraphStage::returnId(void)
{
  return(id);
}

unsigned long GanitaGraphStage::returnValue(void)
{
  return(value);
}

unsigned long GanitaGraphStage::addNode(unsigned long val, string edgeval)
{
  GanitaNode *tmpNode = new GanitaNode();

  tmpNode->setId((unsigned long)stagenode.size() + 1);
  tmpNode->setValue(val);
  tmpNode->setEdge(edgeval);

  stagenode.push_back(std::make_shared<GanitaNode>(*tmpNode));
  delete tmpNode;

  return((unsigned long)stagenode.size());
}

unsigned long GanitaGraphStage::addNode(string edgeval)
{
  GanitaNode *tmpNode = new GanitaNode();

  tmpNode->setId((unsigned long)stagenode.size() + 1);
  tmpNode->setValue((unsigned long)stagenode.size() + 1);
  tmpNode->setEdge(edgeval);

  stagenode.push_back(std::make_shared<GanitaNode>(*tmpNode));
  delete tmpNode;

  return((unsigned long)stagenode.size());
}

unsigned long GanitaGraphStage::returnNumNodes(void)
{
  return(stagenode.size());
}

GanitaNode *GanitaGraphStage::returnNode(unsigned long nn)
{
  if(stagenode.size() <= 0){
    // no nodes added yet
    return(NULL);
  }

  return(stagenode[nn % stagenode.size()].get());
}

