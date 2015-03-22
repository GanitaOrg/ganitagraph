#include "ganita/graph/GanitaGraphCluster.hpp"

// GanitaNode id will equal a pattern from the data stream. 
// GanitaNode value will equal the count for pattern. 
// Each GanitaNode will contain a single GanitaEdge. 
// Each GanitaEdge will point to the next GanitaNode.

GanitaGraphCluster::GanitaGraphCluster(void)
{
  id = 0;
  value = 0;
  num_modes = 0;
}

GanitaGraphCluster::GanitaGraphCluster(uint64_t nm)
{
  id = 0;
  value = 0;
  num_modes = nm;
}

uint64_t GanitaGraphCluster::addNew(string prop)
{
  uint64_t ii, jj;
  GanitaEdge ed;
  GanitaNode *tmpNode = new GanitaNode();
  uint64_t len;
  uint64_t diff;
  uint64_t min;
  uint64_t min_i;

  // Add another node.
  tmpNode->setId(node.size());
  tmpNode->setValue(1);
  //tmpNode->addEdge(0,0);
  tmpNode->initProperty(prop);
  node.push_back(std::make_shared<GanitaNode>(*tmpNode));
  delete tmpNode;
  
  if(modes.size() < num_modes){
    // Add another mode.
    modes.push_back(node.size() - 1);
    return(1);
  }

  ii = 0; diff = 0; 
  min = 0; min_i = 0;
  while(node[modes[ii]]->returnProperty() != prop){
    // Find the mode with minimum Lp difference. 
    if(prop.size() < node[modes[ii]]->returnProperty().size()){
      len = prop.size();
    }
    for(jj=0; jj<len; jj++){
      diff += abs(subtract(prop[jj],node[modes[ii]]->returnProperty()[jj]));
    }
    if(diff < min){
      // Found new minimum mode. 
      min = diff;
      min_i = ii;
    }
  }
  // Add edge between new node and min mode.
  node[node.size()-1]->addEdge(0,modes[min_i]);

  return(node.size());
}

uint64_t GanitaGraphCluster::dumpList(void)
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

int GanitaGraphCluster::subtract(char b1, char b2)
{
  return((int)((unsigned char) b1) - ((unsigned char) b2));
}

