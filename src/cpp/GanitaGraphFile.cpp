#include "ganita/graph/GanitaGraphFile.hpp"

GanitaGraphFile::GanitaGraphFile(void)
{
  gg_fixed_buf_size = GANITA_DEFAULT_GRAPH_BUFFER_SIZE;
  gg_buf_size = gg_fixed_buf_size;
  gg_buffer_num = 0;
  gg_buf_start = 0;
  gg_file_size = 0;
}

uint64_t GanitaGraphFile::openGraphFile(char buf_file[])
{
  // Open input, output graph file.
  strcpy(file_name, buf_file);
  gg_graph_file.open(buf_file, ios::in | ios::out | ios::binary | ios::trunc);
  if (!gg_graph_file.is_open()){
    std::cout<<"Unable to open graph file: "<<buf_file<<std::endl;
    return(0);
  }
  //cout<<"Out buf size: "<<out_buf_size<<endl;
  //out_byte_value = new unsigned char[out_buf_size];
  
  return(1);
}

// This will setup file for large updates. 
// Currently, location is hard-coded in typical linux tmp dir. 
uint64_t GanitaGraphFile::createGraphFile(void)
{
  const char dir_path[] = "/tmp/ganita";
  mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUSR);
  openGraphFile((char *) "/tmp/ganita/graph");

  return(1);
}

int GanitaGraphFile::writeGraphHeader(GanitaGraph *mygg)
{
  if(!gg_graph_file.is_open()){
    std::cout<<"Did not open graph file."<<std::endl;
    return(-1);
  }
  char gbuf[16];
  uint64_t num;
  cout<<"Writing out graph header."<<endl;
  strcpy(gbuf, "GanitaGraph");
  //gg_graph_file.seekp(0);
  gg_graph_file.write(gbuf, 11);
  num = mygg->returnId();
  gg_graph_file.write(reinterpret_cast<const char *>(&num), sizeof(uint64_t));
  num = mygg->returnValue();
  gg_graph_file.write(reinterpret_cast<const char *>(&num), sizeof(uint64_t));
  num = mygg->returnNumNodes();
  gg_graph_file.write(reinterpret_cast<const char *>(&num), sizeof(uint64_t));

  return(35);
}

int GanitaGraphFile::writeGraph(GanitaGraph *mygg)
{
  if(!gg_graph_file.is_open()){
    std::cout<<"Did not open graph file."<<std::endl;
    return(-1);
  }
  uint64_t ii, num;
  writeGraphHeader(mygg);
  num = mygg->returnNumNodes();
  for(ii=0; ii<num; ii++){
    writeGraphNodeEdges(mygg->returnNode(ii));
  }

  return(num);
}

int GanitaGraphFile::writeGraphNode(GanitaNode *mygn)
{
  if(!gg_graph_file.is_open()){
    std::cout<<"Did not open graph file."<<std::endl;
    return(-1);
  }
  char gbuf[16];
  uint64_t num;
  cout<<"Writing out graph node."<<endl;
  strcpy(gbuf, "GanitaNode");
  //gg_graph_file.seekp(0);
  gg_graph_file.write(gbuf, 10);
  num = mygn->returnId();
  gg_graph_file.write(reinterpret_cast<const char *>(&num), sizeof(uint64_t));
  num = mygn->returnValue();
  gg_graph_file.write(reinterpret_cast<const char *>(&num), sizeof(uint64_t));
  num = mygn->returnNumEdges();
  gg_graph_file.write(reinterpret_cast<const char *>(&num), sizeof(uint64_t));

  return(34);
}

int GanitaGraphFile::writeGraphNodeEdges(GanitaNode *mygn)
{
  if(!gg_graph_file.is_open()){
    std::cout<<"Did not open graph file."<<std::endl;
    return(-1);
  }
  uint64_t num;
  uint64_t ii;
  GanitaEdge myedge;
  writeGraphNode(mygn);
  num = mygn->returnNumEdges();
  for(ii=0; ii<num; ii++){
    mygn->returnEdge(ii, myedge);
    writeGraphEdge(&myedge);
  }

  return(34);
}

int GanitaGraphFile::writeGraphEdge(GanitaEdge *myge)
{
  if(!gg_graph_file.is_open()){
    std::cout<<"Did not open graph file."<<std::endl;
    return(-1);
  }
  char gbuf[16];
  uint64_t num;
  cout<<"Writing out node edges."<<endl;
  strcpy(gbuf, "GanitaEdge");
  //gg_graph_file.seekp(0);
  gg_graph_file.write(gbuf, 10);
  num = myge->returnId();
  gg_graph_file.write(reinterpret_cast<const char *>(&num), sizeof(uint64_t));
  num = myge->returnValue();
  gg_graph_file.write(reinterpret_cast<const char *>(&num), sizeof(uint64_t));

  return(26);
}

int GanitaGraphFile::close(void)
{
  if(gg_graph_file.is_open()){
    //cout<<"Closing graph file."<<endl;
    gg_graph_file.close();
  }
  
  return(1);
}

int GanitaGraphFile::writeVisTables(GanitaGraph *ga)
{
  char vis_file[] = "/var/www/html/graph/graph1.html";
  std::fstream gg_vis_file;
  const char dir_path[] = "/var/www/html/graph";
  mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUSR);
  gg_vis_file.open(vis_file, ios::in | ios::out | ios::binary | ios::trunc);
  if (!gg_vis_file.is_open()){
    std::cout<<"Unable to open vis file: "<<vis_file<<std::endl;
    return(0);
  }
  string line;
  char line2[5000];
  uint64_t ii, jj;
  uint64_t num = ga->returnNumNodes();
  GanitaEdge myedge;

  cout<<"Writing vis tables"<<endl;
  line.assign("<html>\n<head>\n<script type=\"text/javascript\" src=\"../js/vis.min.js\"></script>\n<link href=\"../css/vis.min.css\" rel=\"stylesheet\" type=\"text/css\" />\n<style type=\"text/css\">\n #mynetwork {width: 1200px; height: 800px; border: 1px solid lightgray;}\n</style>\n</head>\n<body>\n<div id=\"mynetwork\"></div>");
  gg_vis_file.write(line.c_str(), line.size());

  line.assign("<script type=\"text/javascript\">\n");
  gg_vis_file.write(line.c_str(), line.size());
  line.assign("var nodes = new vis.DataSet([\n");
  gg_vis_file.write(line.c_str(), line.size());
  for(ii=0; ii<num; ii++){
    sprintf(line2, "{id: %ld, label: \'%s\'},\n", 
	    ga->returnNode(ii)->returnId(), ga->returnNode(ii)->returnProperty().c_str());
    line.assign(line2);
    gg_vis_file.write(line.c_str(), line.size());
  }
  line.assign("]);\n\n");
  gg_vis_file.write(line.c_str(), line.size());
  line.assign("var edges = new vis.DataSet([\n");
  gg_vis_file.write(line.c_str(), line.size());
  for(ii=0; ii<num; ii++){
    for(jj=0; jj<ga->returnNode(ii)->returnNumEdges(); jj++){
      ga->returnNode(ii)->returnEdge(jj, myedge);
      sprintf(line2, "{from: %ld, to: \'%ld\'},\n", 
	      ga->returnNode(ii)->returnId(), myedge.returnValue());
      line.assign(line2);
      gg_vis_file.write(line.c_str(), line.size());
    }
  }
  line.assign("]);\n\n");
  gg_vis_file.write(line.c_str(), line.size());

  line.assign("var container = document.getElementById(\'mynetwork\');\nvar data = {nodes: nodes, edges: edges};\nvar options = {edges:{physics: true, smooth: {enabled: true,type: \'dynamic\',roundness: 0.5},title:undefined},layout: {randomSeed: undefined,hierarchical: {enabled:false,levelSeparation: 150,direction: \'UD\', sortMethod: 'directed'}}}; var network = new vis.Network(container, data, options); </script> </body> </html>\n");
  gg_vis_file.write(line.c_str(), line.size());

  gg_vis_file.close();

  return(1);
}

int GanitaGraphFile::writeVisTablesForAdic(GanitaGraph *ga)
{
  char vis_file[] = "/var/www/html/graph/graph1.html";
  std::fstream gg_vis_file;
  const char dir_path[] = "/var/www/html/graph";
  mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUSR);
  gg_vis_file.open(vis_file, ios::in | ios::out | ios::binary | ios::trunc);
  if (!gg_vis_file.is_open()){
    std::cout<<"Unable to open vis file: "<<vis_file<<std::endl;
    return(0);
  }
  string line;
  char line2[5000];
  uint64_t ii, jj;
  uint64_t num = ga->returnNumNodes();
  GanitaEdge myedge;

  cout<<"Writing vis tables"<<endl;
  line.assign("<html>\n<head>\n<script type=\"text/javascript\" src=\"../js/vis.min.js\"></script>\n<link href=\"../css/vis.min.css\" rel=\"stylesheet\" type=\"text/css\" />\n<style type=\"text/css\">\n #mynetwork {width: 1200px; height: 800px; border: 1px solid lightgray;}\n</style>\n</head>\n<body>\n<div id=\"mynetwork\"></div>");
  gg_vis_file.write(line.c_str(), line.size());

  line.assign("<script type=\"text/javascript\">\n");
  gg_vis_file.write(line.c_str(), line.size());
  line.assign("var nodes = new vis.DataSet([\n");
  gg_vis_file.write(line.c_str(), line.size());
  // Write out root node. 
  for(ii=0; ii<1; ii++){
    sprintf(line2, "{id: %ld, label: \'%s\', color: \'#99ff99\'},\n", 
	    ga->returnNode(ii)->returnId(), ga->returnNode(ii)->returnProperty().c_str());
    line.assign(line2);
    gg_vis_file.write(line.c_str(), line.size());
  }
  // Write out 2 observation nodes.
  for(ii=1; ii<3; ii++){
    sprintf(line2, "{id: %ld, label: \'%s\', color: \'#ff9999\'},\n", 
	    ga->returnNode(ii)->returnId(), ga->returnNode(ii)->returnProperty().c_str());
    line.assign(line2);
    gg_vis_file.write(line.c_str(), line.size());
  }
  // Write out hidden nodes. 
  for(ii=3; ii<num; ii++){
    sprintf(line2, "{id: %ld, label: \'%s\'},\n", 
	    ga->returnNode(ii)->returnId(), ga->returnNode(ii)->returnProperty().c_str());
    line.assign(line2);
    gg_vis_file.write(line.c_str(), line.size());
  }
  line.assign("]);\n\n");
  gg_vis_file.write(line.c_str(), line.size());
  line.assign("var edges = new vis.DataSet([\n");
  gg_vis_file.write(line.c_str(), line.size());
  for(ii=0; ii<num; ii++){
    for(jj=0; jj<ga->returnNode(ii)->returnNumEdges(); jj++){
      ga->returnNode(ii)->returnEdge(jj, myedge);
      sprintf(line2, "{from: %ld, to: \'%ld\'},\n", 
	      ga->returnNode(ii)->returnId(), myedge.returnValue());
      line.assign(line2);
      gg_vis_file.write(line.c_str(), line.size());
    }
  }
  line.assign("]);\n\n");
  gg_vis_file.write(line.c_str(), line.size());

  line.assign("var container = document.getElementById(\'mynetwork\');\nvar data = {nodes: nodes, edges: edges};\nvar options = {edges:{physics: true, smooth: {enabled: true,type: \'dynamic\',roundness: 0.5},title:undefined},layout: {randomSeed: undefined,hierarchical: {enabled:false,levelSeparation: 150,direction: \'UD\', sortMethod: 'directed'}}}; var network = new vis.Network(container, data, options); </script> </body> </html>\n");
  gg_vis_file.write(line.c_str(), line.size());

  gg_vis_file.close();

  return(1);
}

