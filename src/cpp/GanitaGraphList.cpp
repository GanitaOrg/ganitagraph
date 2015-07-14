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

uint64_t GanitaGraphList::setId(uint64_t ii)
{
  id = ii;
  return(id);
}

uint64_t GanitaGraphList::setValue(uint64_t val)
{
  value = val;
  return(value);
}

uint64_t GanitaGraphList::returnId(void)
{
  return(id);
}

uint64_t GanitaGraphList::returnValue(void)
{
  return(value);
}

uint64_t GanitaGraphList::addNew(uint64_t the_id)
{
  uint64_t ii;
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
    //cout<<"Previous node: "<<node[ii]->returnId()<<endl;
    //cout<<"New node: "<<the_id<<endl;
    //cout<<"New edge value: "<<ed.returnValue()<<endl;
    tmpNode->addEdge(ii,ed.returnValue());
    node.push_back(std::make_shared<GanitaNode>(*tmpNode));
    // change previous node to point to new node.
    node[ed.returnValue()]->setEdgeId(0,node.size()-1);
    node[ii]->setEdgeValue(0,node.size()-1);
  }

  delete tmpNode;
  return(node.size());
}

// This method will automatically track a fixed number of max values. 
// It will automatically update the linked list with any new max 
// values that are in the top listsize values (i.e. the_id). 
uint64_t GanitaGraphList::buildMaxList(uint64_t the_id, uint64_t nv, uint64_t listsize)
{
  uint64_t ii, newvalue;
  GanitaEdge ed;
  GanitaNode *tmpNode = new GanitaNode();
  // Set GanitaGraphList id to max node index
  // Set GanitaGraphList value to min node index.
  // This helps bookkeeping of list. 
  // Each node has a single edge. 
  // id of edge points to next smallest node. 
  // value of edge points to next biggest node. 

  if(node.size() == 0){
    // add first node
    tmpNode->setId(the_id);
    tmpNode->setValue(nv);
    tmpNode->addEdge(0,0);
    node.push_back(std::make_shared<GanitaNode>(*tmpNode));
    delete tmpNode;
    id = 0;
    value = 0;
    return(1);
  }

  // This method runs fast, because most times 
  // it does not need to update the list. 
  if((node.size() >= listsize) && (node[value]->returnId() >= the_id)){
    // No need to add change the list
    return(node.size());
  }

  ii = id;
  while(node[ii]->returnId() > the_id){
    if(ii == value){
      // Cycled back to beginning of list.
      // From check above, we know node.size() < listsize. 
      // Add new node at end of list.
      tmpNode->setId(the_id);
      tmpNode->setValue(nv);
      tmpNode->addEdge(id,value);
      node.push_back(std::make_shared<GanitaNode>(*tmpNode));
      // change previous node to point to new node.
      node[ii]->setEdgeId(0,node.size()-1);
      value = node.size() - 1;
      node[id]->setEdgeValue(0,node.size()-1);
      delete tmpNode;
      return(node.size());
    } 
    node[ii]->returnEdge(0, ed);
    ii = ed.returnId();
  }

  if(node.size() < listsize){
    // add new node and point to next node.
    if(ii == id){id = node.size();}
    tmpNode->setId(the_id);
    tmpNode->setValue(nv);
    node[ii]->returnEdge(0, ed);
    //cout<<"Previous node: "<<node[ii]->returnId()<<endl;
    //cout<<"New node: "<<the_id<<endl;
    //cout<<"New edge value: "<<ed.returnValue()<<endl;
    tmpNode->addEdge(ii,ed.returnValue());
    node.push_back(std::make_shared<GanitaNode>(*tmpNode));
    // change previous node to point to new node.
    node[ed.returnValue()]->setEdgeId(0,node.size()-1);
    node[ii]->setEdgeValue(0,node.size()-1);
  }
  else {
    // replace node
    if(ii == id){id = value;}
    node[value]->returnEdge(0, ed);
    newvalue = ed.returnValue();
    node[ii]->returnEdge(0, ed);
    node[value]->setId(the_id);
    node[value]->setValue(nv);
    node[value]->setEdgeId(0, ii);
    if(ed.returnValue() == value){
      node[value]->setEdgeValue(0, newvalue);
    }
    else{
      node[value]->setEdgeValue(0, ed.returnValue());
      node[ed.returnValue()]->setEdgeId(0,value);
    }
    node[id]->setEdgeValue(0, newvalue);
    node[ii]->setEdgeValue(0, value);
    node[newvalue]->setEdgeId(0,id);
    value = newvalue;
  }

  delete tmpNode;
  return(node.size());
}

uint64_t GanitaGraphList::dumpList(void)
{
  uint64_t ii;

  cout<<"Number of nodes: "<<returnNumNodes()<<endl;
  for(ii=0; ii<returnNumNodes(); ii++){
    cout<<"Node: "<<ii<<" | "<<returnNode(ii)->returnId()
	<<" | "<<returnNode(ii)->returnValue()<<endl;
    returnNode(ii)->dumpEdgeAll();
  }

  return(node.size());
}

uint64_t GanitaGraphList::dumpList2(void)
{
  uint64_t ii, count;
  GanitaEdge ed;

  count = 0; ii = id;
  cout<<"Number of nodes: "<<returnNumNodes()<<endl;
  cout<<"id/value: "<<returnId()<<"/"<<returnValue()<<endl;
  while(count < returnNumNodes()){
    cout<<"Node: "<<ii<<" | "<<returnNode(ii)->returnId()
	<<" | "<<returnNode(ii)->returnValue()<<endl;
    returnNode(ii)->dumpEdgeAll();
    returnNode(ii)->returnEdge(0, ed);
    ii = ed.returnId();
    count++;
  }

  return(node.size());
}

