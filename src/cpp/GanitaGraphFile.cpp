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

int GanitaGraphFile::close(void)
{
  if (gg_graph_file.is_open()){
    //cout<<"Closing graph file."<<endl;
    gg_graph_file.close();
  }
  
  return(1);
}

