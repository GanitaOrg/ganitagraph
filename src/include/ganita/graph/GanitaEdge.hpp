// g++ -O3 GanitaEdge.c -o GanitaEdge -lm

#ifndef _GANITAEDGE_
#define _GANITAEDGE_

#include <cstdint>
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
  uint64_t id;
  uint64_t value;
public:
  GanitaEdge(void);
  GanitaEdge(uint64_t ii, uint64_t vv);
  uint64_t returnId(void);
  uint64_t returnValue(void);
  uint64_t setId(uint64_t ii);
  uint64_t setValue(uint64_t val);
};

#endif
