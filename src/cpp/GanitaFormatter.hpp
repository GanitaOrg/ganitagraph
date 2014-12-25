// g++ -O3 neo4jFormatter.c -o neo4jFormatter -lm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

class Neo4jFormatter
{
private:
  long total;
  vector<string> nodes1;
  vector<string> nodes2;
  string node_csv;
  string rel_csv;
public:
  Neo4jFormatter();
  int readCSV(ifstream myfile);
  long readCSV(char *myfilestr);
  long readCSV(char *myfilestr,char *myfilestr2,char *myfilestr3);
};

