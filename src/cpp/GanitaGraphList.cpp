#include "ganita/graph/GanitaGraphList.hpp"

// GanitaNode id will equal a pattern from the data stream. 
// GanitaNode value will equal the count for pattern. 
// Each GanitaNode will contain a single GanitaEdge. 
// Each GanitaEdge will point to the next GanitaNode.

GanitaGraphList::GanitaGraphList(void)
{
  id = 0;
  value = 0;
}

GanitaGraphList::GanitaGraphList(int verbose)
{
  id = 0;
  value = 0;
  verbosity = verbose;
}

unsigned long GanitaGraphList::addNew(unsigned long the_id)
{
  unsigned long ii;
  GanitaEdge ed;
  GanitaNode *tmpNode = new GanitaNode();

  if(node.size() == 0){
    // add first node
    tmpNode->setId(the_id);
    tmpNode->setValue(1);
    tmpNode->addEdge(0,0);
    node.push_back(std::make_shared<GanitaNode>(*tmpNode));
    delete tmpNode;
    return(1);
  }

  ii = 0;
  while(node[ii]->returnId() < the_id){
    node[ii]->returnEdge(0, ed);
    if(ed.returnId() == 0){
      // cycled back to beginning of list.
      tmpNode->setId(the_id);
      tmpNode->setValue(1);
      tmpNode->addEdge(0,ii);
      node.push_back(std::make_shared<GanitaNode>(*tmpNode));
      // change previous node to point to new node.
      node[ii]->setEdgeId(0,node.size()-1);
      if(node.size() == 2){
	node[ii]->setEdgeValue(0,1);
      }
      delete tmpNode;
      return(node.size());
    }
    ii = ed.returnId();
  }

  if(node[ii]->returnId() == the_id){
    // add to counter
    node[ii]->setValue(node[ii]->returnValue() + 1);
  }
  else {
    // add new node and point to next node.
    tmpNode->setId(the_id);
    tmpNode->setValue(1);
    node[ii]->returnEdge(0, ed);
    cout<<"Previous node: "<<node[ii]->returnId()<<endl;
    cout<<"New node: "<<the_id<<endl;
    cout<<"New edge value: "<<ed.returnValue()<<endl;
    tmpNode->addEdge(ii,ed.returnValue());
    node.push_back(std::make_shared<GanitaNode>(*tmpNode));
    // change previous node to point to new node.
    node[ed.returnValue()]->setEdgeId(0,node.size()-1);
    node[ii]->setEdgeValue(0,node.size()-1);
  }

  delete tmpNode;
  return(node.size());
}

unsigned long GanitaGraphList::dumpList(void)
{
  unsigned long ii;

  cout<<"Number of nodes: "<<returnNumNodes()<<endl;
  for(ii=0; ii<returnNumNodes(); ii++){
    cout<<"Node: "<<ii<<" | "<<returnNode(ii)->returnId()
	<<" | "<<returnNode(ii)->returnValue()<<endl;
    returnNode(ii)->dumpEdgeAll();
  }

  return(node.size());
}

