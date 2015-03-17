// g++ -O3 GanitaTrace.c -o GanitaTrace -lm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

class GanitaTrace
{
private:
  // trace[0] contains the nodes 
  // and trace[1] contains the edges. 
  vector<int64_t> trace[2];
  int64_t kink;
public:
  GanitaTrace();
  int64_t findKink();
};

