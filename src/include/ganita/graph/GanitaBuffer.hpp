// This class is used to buffer data in memory and on disk. 
// It includes 3 different file streams. 
// gzt_input_file is used to input data from disk. 
// gzt_output_file is used to output results to disk. 
// gzt_inout_file is used to buffer data to disk. 
// Various memory buffers may be defined. 
// Initially, only a single byte_value buffer is used
// for the gzt_input_file buffering. 

#ifndef _GANITABUFFER_
#define _GANITABUFFER_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>

//default buffer size (1M)
#ifndef GANITA_DEFAULT_BUFFER_SIZE
#define GANITA_DEFAULT_BUFFER_SIZE 1000000
#endif

//default output buffer size
#ifndef GANITA_DEFAULT_OUTPUT_BUFFER_SIZE
#define GANITA_DEFAULT_OUTPUT_BUFFER_SIZE 4096
#endif

//default file buffer size
#ifndef GANITA_DEFAULT_INOUT_BUFFER_SIZE
#define GANITA_DEFAULT_INOUT_BUFFER_SIZE 4096
#endif

using namespace std;

static const string b64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static const uint64_t ganita64_mask[] = {
0x0, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 
0xff, 0x1ff, 0x3ff, 0x7ff, 0xfff, 0x1fff, 0x3fff, 0x7fff, 
0xffff, 0x1ffff, 0x3ffff, 0x7ffff, 0xfffff, 0x1fffff, 0x3fffff, 0x7fffff, 
0xffffff, 0x1ffffff, 0x3ffffff, 0x7ffffff, 0xfffffff, 0x1fffffff, 0x3fffffff, 0x7fffffff, 
0xffffffff, 0x1ffffffff, 0x3ffffffff, 0x7ffffffff, 
0xfffffffff, 0x1fffffffff, 0x3fffffffff, 0x7fffffffff, 
0xffffffffff, 0x1ffffffffff, 0x3ffffffffff, 0x7ffffffffff, 
0xfffffffffff, 0x1fffffffffff, 0x3fffffffffff, 0x7fffffffffff, 
0xffffffffffff, 0x1ffffffffffff, 0x3ffffffffffff, 0x7ffffffffffff, 
0xfffffffffffff, 0x1fffffffffffff, 0x3fffffffffffff, 0x7fffffffffffff, 
0xffffffffffffff, 0x1ffffffffffffff, 0x3ffffffffffffff, 0x7ffffffffffffff, 
0xfffffffffffffff, 0x1fffffffffffffff, 0x3fffffffffffffff, 0x7fffffffffffffff, 
0xffffffffffffffff
};

class GanitaBuffer
{
private:
  uint64_t file_loc;
  uint64_t buffer_num;
  uint64_t byte_loc;
  unsigned char *byte_value;
  vector<double> double_value;
  uint64_t buffer_size;
  uint64_t fixed_buffer_size;
  uint64_t file_size;
  uint64_t buffer_start;
  int buf_read_flag;
  std::ifstream *gzt_input_file;
  std::ofstream gzt_output_file;
  std::fstream gzt_inout_file;
  unsigned char outByte;
  int outByteOffset;
  unsigned char *out_byte_value;
  uint64_t out_buf_size;
  uint64_t out_buf_offset;
  uint64_t ref_bits;
  uint64_t ref_bit_loc;
  char *zbuf;
  uint64_t inout_buf_size;
  uint64_t inout_fixed_buf_size;
  uint64_t inout_buffer_num;
  uint64_t inout_buf_start;
  uint64_t inout_file_size;
public:
  GanitaBuffer();
  GanitaBuffer(std::ifstream &gzt_file);
  unsigned char getByte(uint64_t loc);
  uint64_t getBit(uint64_t loc);
  uint64_t getBits(uint64_t loc, int nbits);
  int compareBits(uint64_t loc, uint64_t bb, int len);
  uint64_t countBitPat(uint64_t refpat, int len);
  int64_t getLine(char *line);
  uint64_t size();
  uint64_t open(char *input_file);
  uint64_t openDoubleLine(char *input_file);
  uint64_t dumpDoubles(void);
  int32_t getDouble(uint64_t myindex, double &myd);
  uint64_t doubleSize(void);
  uint64_t openOut(char *out_file);
  uint64_t openFileBuffer(char *buf_file);
  uint64_t initInOutBuffer(uint64_t len);
  uint64_t createInOutBuffer(void);
  uint64_t writeBit(unsigned char bit);
  uint64_t writeByte(unsigned char mybyte);
  uint64_t writeByteInOut(unsigned char mybyte, uint64_t pos);
  uint64_t writeBitInOut(unsigned char bit, uint64_t pos);
  uint64_t writeBufByteInOut(unsigned char mybyte, uint64_t pos);
  uint64_t writeBufBitInOut(unsigned char bit, uint64_t pos);
  inline bool is_base64(unsigned char c);
  string b64Encode(unsigned char const* in_bytes,uint64_t in_len);
  string b64Encode(void);
  string b64Decode(string &enc_str);
  int close(void);
};

#endif
