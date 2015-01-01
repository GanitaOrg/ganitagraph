// g++ -O3 GanitaEdge.c -o GanitaEdge -lm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

class GanitaEdge
{
private:
  unsigned long id;
  unsigned long value;
public:
  GanitaEdge(void);
  GanitaEdge(unsigned long ii, unsigned long vv);
  unsigned long returnId(void);
  unsigned long returnValue(void);
};

