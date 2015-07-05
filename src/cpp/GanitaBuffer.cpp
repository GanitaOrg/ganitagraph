#include "ganita/graph/GanitaBuffer.hpp"

GanitaBuffer::GanitaBuffer(void)
{
  file_loc = 0;
  buffer_num = 0;
  buffer_start = 0;
  byte_loc = 0;
  fixed_buffer_size = GANITA_DEFAULT_BUFFER_SIZE;
  buffer_size = fixed_buffer_size;
  out_buf_size = GANITA_DEFAULT_OUTPUT_BUFFER_SIZE;
  //cout<<"Out buf size: "<<out_buf_size<<endl;
  buf_read_flag = 0;
  //gzt_input_file = new std::ifstream();
  outByte = 0;
  outByteOffset = 0;
  out_buf_offset = 0;
  inout_fixed_buf_size = GANITA_DEFAULT_INOUT_BUFFER_SIZE;
  inout_buf_size = inout_fixed_buf_size;
  file_name[0] = '\0';
}

// GanitaBuffer::GanitaBuffer(std::ifstream gzt_file)
// {
//   file_loc = 0;
//   buffer_num = 0;
//   buffer_start = 0;
//   byte_loc = 0;
//   fixed_buffer_size = GANITA_DEFAULT_BUFFER_SIZE;
//   buffer_size = fixed_buffer_size;
//   //out_buf_size = GANITA_DEFAULT_OUTPUT_BUFFER_SIZE;
//   outByte = 0;
//   outByteOffset = 0;
//   out_buf_offset = 0;
//   inout_fixed_buf_size = GANITA_DEFAULT_INOUT_BUFFER_SIZE;
//   inout_buf_size = inout_fixed_buf_size;
//   if (!gzt_file.is_open()){
//     std::cout<<"Unable to open input file: "<<std::endl;
//     buf_read_flag = 0;
//   }
//   else {
//     byte_value = new unsigned char[buffer_size];
//     //gzt_input_file = new std::ifstream();
//     //gzt_input_file = &gzt_file;
//     gzt_input_file = gzt_file;
//     gzt_input_file->seekg(0, gzt_input_file.end);
//     file_size = gzt_input_file.tellg();
//     if(file_size < buffer_size){
//       buffer_size = file_size;
//     }
//     gzt_input_file.seekg(0, gzt_input_file.beg);
//     gzt_input_file.read((char *) byte_value,buffer_size);
//     buf_read_flag = 1;
//   }
// }

// Could be most important method in this class. 
// Used to read from input file and 
// do automatic buffering in memory. 
unsigned char GanitaBuffer::getByte(uint64_t loc)
{
  unsigned char byte;

  if(loc >= file_size){
    cout<<"Location beyond file end: "<<loc<<" >= "<<file_size<<endl;
    loc = loc % file_size;
  }
  if(buf_read_flag <= 0){
    std::cout<<"Did not open input file."<<std::endl;
    return(0);
  }

  file_loc = loc;
  if((loc < buffer_start) || (loc >= buffer_start + buffer_size))
    {
      // Need to read a new buffer
      //cout<<"Read new buffer "<<loc<<" "<<buffer_start<<"\n";
      buffer_num = loc / fixed_buffer_size;
      buffer_start = buffer_num * fixed_buffer_size;
      byte_loc = file_loc - buffer_start;
      gzt_input_file.seekg(0, gzt_input_file.beg);
      gzt_input_file.seekg(buffer_start);
      if(buffer_start + buffer_size >= file_size){
	buffer_size = file_size - buffer_start;
      }
      else buffer_size = fixed_buffer_size;
      gzt_input_file.read((char *) byte_value,buffer_size);
      byte = byte_value[byte_loc];
    }
  else {
    // Get byte from current buffer
    byte_loc = file_loc - buffer_start;
    byte = byte_value[byte_loc];
  }

  return(byte & 0xff);
}

// Could be most important method in this class. 
// Used to read from input file and 
// do automatic buffering in memory. 
unsigned char GanitaBuffer::getInOutByte(uint64_t loc)
{
  unsigned char byte;

  if(loc >= inout_file_size){
    cout<<"Location beyond inout file end: "<<loc<<" >= "
	<<inout_file_size<<endl;
    loc = loc % inout_file_size;
  }

  if(!gzt_inout_file.is_open()){
    std::cout<<"Did not open inout file."<<std::endl;
    return(0);
  }

  if((loc < inout_buf_start) || (loc >= inout_buf_start + inout_buf_size))
    {
      inout_buf_start = loc;
      if(inout_fixed_buf_size > inout_file_size - loc){
	inout_buf_size = inout_file_size - loc;
	//cout<<"Location near end of inout file end: "<<loc<<" >= "
	//  <<inout_file_size<<endl;	
      }
      else inout_buf_size = inout_fixed_buf_size;
      gzt_inout_file.seekg(0, gzt_input_file.beg);
      gzt_inout_file.seekg(loc);
      gzt_inout_file.read(zbuf,inout_buf_size);
      byte = zbuf[0];
    }
  else {
    // Get byte from current buffer 
    byte = zbuf[loc-inout_buf_start];
  }

  return(byte & 0xff);
}

// Get a bit from input buffer using low to high. 
uint64_t GanitaBuffer::getBit(uint64_t loc){
  uint64_t b1, bottom;
  uint64_t mybit;
  b1 = loc / 8;
  bottom = loc % 8;
  mybit = (uint64_t) (((getByte(b1) & 0xff) >> bottom) & 0x1);
  return(mybit);
}

// Get a bit from input buffer using low to high. 
uint64_t GanitaBuffer::getInOutBit(uint64_t loc){
  uint64_t b1, bottom;
  uint64_t mybit;
  b1 = loc / 8;
  bottom = loc % 8;
  mybit = (uint64_t) (((getInOutByte(b1) & 0xff) >> bottom) & 0x1);
  return(mybit);
}

// Return 1 if any of next len bits are 1.
uint64_t GanitaBuffer::getInOutBit(uint64_t loc, int len){
  int ii = 0;
  while(!getInOutBit(loc + ii)){
    ii++;
    if(ii>=len) return(0);
  }
  return(1);
}

// Get uint64_t of at most 64 bits.
uint64_t GanitaBuffer::getBits(uint64_t loc, int nbits)
{
  uint64_t mybits;
  int ii;
  if(nbits > 64) nbits = 64;
  mybits = 0;
  for(ii=0; ii<nbits; ii++){
    mybits |= (getBit(loc + ii) << ii);
  }
  return(mybits);
}

// Check for match bit string.
int GanitaBuffer::compareBits(uint64_t loc, uint64_t bb, int len)
{
  uint64_t mbits;
  mbits = getBits(loc, len);
  if(mbits == bb) return(1);
  else return(0);
}

// Count occurrences of bit string.
uint64_t GanitaBuffer::countBitPat(uint64_t refpat, int len)
{
  uint64_t ii, count;
  uint64_t tarpat;
  tarpat = getBits(0,len);
  count = 0;
  ii = len - 1;
  while(ii<8*file_size){
    if(tarpat == refpat){
      count++;
      ii += len;
      tarpat = getBits(ii, len);
    }
    else {
      ii++;
      tarpat = (tarpat >> 1) | (getBit(ii) << len);
    }
  }
  return(count);
}

// Read input one line at a time.
// Do not use with getByte currently.
int64_t GanitaBuffer::getLine(char *line)
{
  //char line[101];

  line[0] = '\0';

  if(!gzt_input_file.getline(line,100)){
    // error reading line
    if(gzt_input_file.eof()){              // check for EOF
      std::cout << "[EoF reached]\n";
      return(-1);
    }
    else{
      std::cout << "[error reading]\n";
      return(-2);
    }
  }

  return(strlen(line));
}

uint64_t GanitaBuffer::size()
{
  return(file_size);
}

uint64_t GanitaBuffer::open(char *input_file)
{
  // Open buffer for reading.
  strcpy(file_name, input_file);
  gzt_input_file.open(input_file);
  if (!gzt_input_file.is_open()){
    std::cout<<"Unable to open input file: "<<input_file<<std::endl;
    return(0);
  }

  byte_value = new unsigned char[buffer_size];
  gzt_input_file.seekg(0, gzt_input_file.end);
  file_size = gzt_input_file.tellg();
  if(file_size < buffer_size){
    buffer_size = file_size;
  }
  gzt_input_file.seekg(0, gzt_input_file.beg);
  gzt_input_file.read((char *) byte_value,buffer_size);
  buf_read_flag = 1;
  
  return(1);
}

char *GanitaBuffer::returnFileName(void)
{
  return(file_name);
}

uint64_t GanitaBuffer::openDoubleLine(char *input_file)
{
  // Open buffer for reading.
  char line[101];
  double val;
  gzt_input_file.open(input_file);
  if (!gzt_input_file.is_open()){
    std::cout<<"Unable to open input file: "<<input_file<<std::endl;
    return(0);
  }

  while(getLine(&line[0]) > 0){
    //cout<<"Found another line"<<endl;
    sscanf(line,"%lf",&val);
    double_value.push_back(val);
  }

  cout<<"Sequence contains "<<double_value.size()<<" doubles."<<endl;
  
  // byte_value = new unsigned char[buffer_size];
  // gzt_input_file->seekg(0, gzt_input_file->end);
  // file_size = gzt_input_file->tellg();
  // if(file_size < buffer_size){
  //   buffer_size = file_size;
  // }
  // gzt_input_file->seekg(0, gzt_input_file->beg);
  // gzt_input_file->read((char *) byte_value,buffer_size);
  // buf_read_flag = 1;

  return(double_value.size());
}

uint64_t GanitaBuffer::dumpDoubles(void)
{
  uint64_t ii;
  for(ii=0; ii<double_value.size(); ii++){
    fprintf(stdout, "%lf\n", double_value[ii]);
  }
  return(double_value.size());
}

int32_t GanitaBuffer::getDouble(uint64_t myindex, double &myd)
{
  if(double_value.size() <= 0){
    return(-1);
  }
  else{
    if(myindex >= double_value.size()){
      myindex %= double_value.size();
      myd = double_value[myindex];
      return(0);
    }
    else {
      myd = double_value[myindex];
      return(1);
    }
  }
}      

uint64_t GanitaBuffer::doubleSize(void)
{
  return(double_value.size());
}

uint64_t GanitaBuffer::openOut(char *out_file)
{
  // Open output file for writing.
  gzt_output_file.open(out_file);
  if (!gzt_output_file.is_open()){
    std::cout<<"Unable to open output file: "<<out_file<<std::endl;
    return(0);
  }
  //cout<<"Out buf size: "<<out_buf_size<<endl;
  out_byte_value = new unsigned char[out_buf_size];
  
  return(1);
}

uint64_t GanitaBuffer::openFileBuffer(char buf_file[])
{
  // Open output file for writing.
  //gzt_inout_file.open(buf_file, ios::in | ios::out | ios::binary);
  gzt_inout_file.open(buf_file, ios::in | ios::out | ios::binary | ios::trunc);
  if (!gzt_inout_file.is_open()){
    std::cout<<"Unable to open inout file: "<<buf_file<<std::endl;
    return(0);
  }
  //cout<<"Out buf size: "<<out_buf_size<<endl;
  //out_byte_value = new unsigned char[out_buf_size];
  
  return(1);
}

uint64_t GanitaBuffer::initInOutBuffer(uint64_t len)
{
  // len is the number of bytes to set to zero.
  if (!gzt_inout_file.is_open()){
    std::cout<<"inout file is not open: "<<std::endl;
    return(0);
  }
  //char *zbuf = new char[inout_buf_size]();
  
  if(len < inout_fixed_buf_size){
    inout_fixed_buf_size = len;
    inout_buf_size = len;
  }
  inout_file_size = len;
  inout_buffer_num = 0;
  inout_buf_start = 0;
  zbuf = new char[inout_fixed_buf_size]();
  uint64_t jj = len / inout_buf_size;
  uint64_t kk = len - jj * inout_buf_size;
  uint64_t ii;
  //cout<<"sizes: "<<inout_buf_size<<" "<<kk<<endl;
  for(ii=0; ii<jj; ii++){
    gzt_inout_file.write(zbuf, inout_buf_size);
  }
  gzt_inout_file.write(zbuf, kk);
  
  return(len);
}

// This will setup file buffer for large updates. 
// Currently, location is hard-coded in typical linux tmp dir. 
uint64_t GanitaBuffer::createInOutBuffer(void)
{
  const char dir_path[] = "/tmp/ganita";
  //boost::filesystem::path dir(dir_path);
  //if(
  mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUSR);
  //   < 0){
  //fprintf(stderr, "Unable to make directory: %s.\n", dir_path);
  //return(0);
  //}
  // if(!boost::filesystem::create_directory(dir)) {
  //   std::cout << "Could not create /tmp/ganita directory." << "\n";
  // }
  openFileBuffer((char *) "/tmp/ganita/gzero.track");
  // we need a bit for each input file bit.
  //cout<<"File size: "<<(file_size + 7)/8<<endl;
  // Bytes are samples. 
  //initInOutBuffer( (file_size + 7)/8 );
  // Bits are samples.
  initInOutBuffer( file_size );

  return(1);
}

// This will setup file buffer for large updates. 
// Currently, location is hard-coded in typical linux tmp dir. 
uint64_t GanitaBuffer::createInOutBuffer(char *inout_file, uint64_t iofs)
{
  const char dir_path[] = "/tmp/ganita";
  char myfname[500];
  //boost::filesystem::path dir(dir_path);
  //if(
  mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUSR);
  //   < 0){
  //fprintf(stderr, "Unable to make directory: %s.\n", dir_path);
  //return(0);
  //}
  // if(!boost::filesystem::create_directory(dir)) {
  //   std::cout << "Could not create /tmp/ganita directory." << "\n";
  // }
  sprintf(myfname, "%s/%s", dir_path, inout_file);
  openFileBuffer(myfname);
  // we need a bit for each input file bit.
  //cout<<"File size: "<<(file_size + 7)/8<<endl;
  // Bytes are samples. 
  //initInOutBuffer( (file_size + 7)/8 );
  // Bits are samples.
  initInOutBuffer( iofs );

  return(1);
}

uint64_t GanitaBuffer::writeBit(unsigned char bit)
{
  outByte |= ((bit & 0x1) << outByteOffset);
  outByteOffset++;
  //cout<<"Offset: "<<outByteOffset<<"| ";
  if(outByteOffset >= 8){
    // save byte to output buffer
    out_byte_value[out_buf_offset] = outByte;
    out_buf_offset++;
    outByte = 0;
    outByteOffset = 0;
  }
  if(out_buf_offset >= out_buf_size){
    // save output buffer to file
    gzt_output_file.write((char *)out_byte_value,out_buf_size);
    out_buf_offset = 0;
  }

  return(out_buf_offset);
}

uint64_t GanitaBuffer::writeByteInOut(unsigned char mybyte, uint64_t pos)
{
  return(writeBufByteInOut(mybyte, pos));
}

uint64_t GanitaBuffer::writeU64InOut(uint64_t dd, uint64_t pos)
{
  int ii, ret;
  for(ii=0; ii<8; ii++){
    ret = writeByteInOut((dd >> 8*ii) & 0xff, pos+ii);
  }
  return(ret);
}

uint64_t GanitaBuffer::write64InOut(int64_t dd, uint64_t pos)
{
  int ii, ret;
  for(ii=0; ii<8; ii++){
    ret = writeByteInOut((dd >> 8*ii) & 0xff, pos+ii);
  }
  return(ret);
}

// Following method does not use memory buffering.
// uint64_t GanitaBuffer::writeByteInOut(unsigned char mybyte, uint64_t pos)
// {
//   // save byte to file buffer
//   gzt_inout_file.seekp(pos);
//   gzt_inout_file.write((char *) &mybyte,1);

//   return(1);
// }

// Low bit before high bit in each byte.
uint64_t GanitaBuffer::writeBitInOut(unsigned char bit, uint64_t pos)
{
  return(writeBufBitInOut(bit, pos));
}

// Following method does not use memory buffering.
// uint64_t GanitaBuffer::writeBitInOut(unsigned char bit, uint64_t pos)
// {
//   uint64_t loc1 = pos / 8;
//   uint64_t loc2 = pos % 8;
//   char tmp1, tmp2;
//   tmp1 = 0x1;
//   gzt_inout_file.seekg (loc1);
//   gzt_inout_file.read (&tmp2, 1);
//   if(bit){
//     tmp2 |= (tmp1 << loc2);
//   }
//   else{
//     tmp2 &= (~(tmp1 << loc2));
//   }
//   //cout<<loc1<<"|"<<tmp2<<"|";
//   gzt_inout_file.seekp(loc1);
//   gzt_inout_file.write(&tmp2, 1);

//   return(1);
// }

uint64_t GanitaBuffer::writeBufByteInOut(unsigned char mybyte, uint64_t pos)
{
  // save byte to memory or file inout buffer
  // pos is a byte position
  if(pos >= inout_file_size){
    // Trying to write beyond claimed inout file size.
    fprintf(stderr, "Trying to write beyond claimed inout file size.\n");
    return(0);
  }
  if((pos >= inout_buf_start + inout_buf_size) || 
     (pos < inout_buf_start)){
    // save current inout buffer and read in new inout buffer
    gzt_inout_file.seekp(inout_buf_start);
    gzt_inout_file.write(zbuf, inout_buf_size);
    // Determine size of next buffer.
    // Next buffer will start at pos.
    if(inout_fixed_buf_size > inout_file_size - pos){
      inout_buf_size = inout_file_size - pos;
    }
    else inout_buf_size = inout_fixed_buf_size;
    // Read inout buffer.
    gzt_inout_file.seekg(pos);
    gzt_inout_file.read(zbuf,inout_buf_size);
    inout_buf_start = pos;
  }
  // Copy mybyte to memory inout buffer.
  zbuf[pos - inout_buf_start] = mybyte;

  return(1);
}

// Need to work on following method.
// Low bit before high bit in each byte.
uint64_t GanitaBuffer::writeBufBitInOut(unsigned char bit, uint64_t pos)
{
  // save bit to memory or file inout buffer
  uint64_t loc1 = pos / 8;
  uint64_t loc2 = pos % 8;
  char tmp1, tmp2;

  if(loc1 >= inout_file_size){
    // Trying to write beyond claimed inout file size.
    fprintf(stderr, "Trying to write beyond claimed inout file size.\n");
    return(0);
  }
  if((loc1 >= inout_buf_start + inout_buf_size) || 
     (loc1 < inout_buf_start)){
    // save current inout buffer and read in new inout buffer
    gzt_inout_file.seekp(inout_buf_start);
    gzt_inout_file.write(zbuf, inout_buf_size);
    // Determine size of next buffer.
    // Next buffer will start at loc1.
    if(inout_fixed_buf_size > inout_file_size - loc1){
      inout_buf_size = inout_file_size - loc1;
    }
    else inout_buf_size = inout_fixed_buf_size;
    // Read inout buffer.
    gzt_inout_file.seekg(loc1);
    gzt_inout_file.read(zbuf,inout_buf_size);
    inout_buf_start = loc1;
  }
  tmp2 = zbuf[loc1 - inout_buf_start];

  tmp1 = 0x1;
  if(bit){
    tmp2 |= (tmp1 << loc2);
  }
  else{
    tmp2 &= (~(tmp1 << loc2));
  }
  //cout<<loc1<<"|"<<tmp2<<"|";
  zbuf[loc1 - inout_buf_start] = tmp2;

  return(1);
}

uint64_t GanitaBuffer::writeByte(unsigned char mybyte)
{
  // save byte to output buffer
  out_byte_value[out_buf_offset] = mybyte;
  out_buf_offset++;
  outByte = 0;
  outByteOffset = 0;
  if(out_buf_offset >= out_buf_size){
    // save output buffer to file
    gzt_output_file.write((char *)out_byte_value,out_buf_size);
    out_buf_offset = 0;
  }

  return(out_buf_offset);
}

inline bool GanitaBuffer::is_base64(unsigned char c) 
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}

string GanitaBuffer::b64Encode(unsigned char const* in_bytes, 
			       uint64_t in_len)
{
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_arr_3[3];
  unsigned char char_arr_4[4];

  while (in_len--) {
    char_arr_3[i++] = *(in_bytes++);
    if (i == 3) {
      char_arr_4[0] = (char_arr_3[0] & 0xfc) >> 2;
      char_arr_4[1] = ((char_arr_3[0] & 0x03) << 4) + ((char_arr_3[1] & 0xf0) >> 4);
      char_arr_4[2] = ((char_arr_3[1] & 0x0f) << 2) + ((char_arr_3[2] & 0xc0) >> 6);
      char_arr_4[3] = char_arr_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += b64_chars[char_arr_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_arr_3[j] = '\0';

    char_arr_4[0] = (char_arr_3[0] & 0xfc) >> 2;
    char_arr_4[1] = ((char_arr_3[0] & 0x03) << 4) + ((char_arr_3[1] & 0xf0) >> 4);
    char_arr_4[2] = ((char_arr_3[1] & 0x0f) << 2) + ((char_arr_3[2] & 0xc0) >> 6);
    char_arr_4[3] = char_arr_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += b64_chars[char_arr_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;
}

string GanitaBuffer::b64Encode(void)
{
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_arr_3[3];
  unsigned char char_arr_4[4];
  uint64_t byte_loc;
  uint64_t in_len;

  byte_loc = 0;
  in_len = file_size;
  while (in_len--) {
    char_arr_3[i++] = getByte(byte_loc++);
    if (i == 3) {
      char_arr_4[0] = (char_arr_3[0] & 0xfc) >> 2;
      char_arr_4[1] = ((char_arr_3[0] & 0x03) << 4) + ((char_arr_3[1] & 0xf0) >> 4);
      char_arr_4[2] = ((char_arr_3[1] & 0x0f) << 2) + ((char_arr_3[2] & 0xc0) >> 6);
      char_arr_4[3] = char_arr_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += b64_chars[char_arr_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_arr_3[j] = '\0';

    char_arr_4[0] = (char_arr_3[0] & 0xfc) >> 2;
    char_arr_4[1] = ((char_arr_3[0] & 0x03) << 4) + ((char_arr_3[1] & 0xf0) >> 4);
    char_arr_4[2] = ((char_arr_3[1] & 0x0f) << 2) + ((char_arr_3[2] & 0xc0) >> 6);
    char_arr_4[3] = char_arr_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += b64_chars[char_arr_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;
}

string GanitaBuffer::b64Decode(string &enc_str)
{
  int in_len = enc_str.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_arr_4[4], char_arr_3[3];
  std::string ret;

  while (in_len-- && ( enc_str[in_] != '=') && is_base64(enc_str[in_])) {
    char_arr_4[i++] = enc_str[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_arr_4[i] = b64_chars.find(char_arr_4[i]);

      char_arr_3[0] = (char_arr_4[0] << 2) + ((char_arr_4[1] & 0x30) >> 4);
      char_arr_3[1] = ((char_arr_4[1] & 0xf) << 4) + ((char_arr_4[2] & 0x3c) >> 2);
      char_arr_3[2] = ((char_arr_4[2] & 0x3) << 6) + char_arr_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_arr_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_arr_4[j] = 0;

    for (j = 0; j <4; j++)
      char_arr_4[j] = b64_chars.find(char_arr_4[j]);

    char_arr_3[0] = (char_arr_4[0] << 2) + ((char_arr_4[1] & 0x30) >> 4);
    char_arr_3[1] = ((char_arr_4[1] & 0xf) << 4) + ((char_arr_4[2] & 0x3c) >> 2);
    char_arr_3[2] = ((char_arr_4[2] & 0x3) << 6) + char_arr_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_arr_3[j];
  }

  return ret;
}

int GanitaBuffer::close(void)
{
  int count;
  count = 0;
  if (!gzt_output_file){
    // write out remaining bytes in output buffer
    //cout<<"Closing output file."<<endl;
    gzt_output_file.write((char *)out_byte_value,out_buf_offset);
    gzt_output_file.close();
    count++;
  }
  if (gzt_input_file.is_open()){
    //cout<<"Closing input file."<<endl;
    gzt_input_file.close();
    count++;
  }
  if (gzt_inout_file.is_open()){
    //cout<<"Closing inout file."<<endl;
    gzt_inout_file.seekp(inout_buf_start);
    gzt_inout_file.write(zbuf, inout_buf_size);
    gzt_inout_file.close();
    count++;
  }
  
  //cout<<"Closed files."<<endl;
  return(count);
}

uint64_t GanitaBuffer::inOutSize(void)
{
  return(inout_file_size);
}

int GanitaBuffer::flushInOut(void)
{
  if (gzt_inout_file.is_open()){
    // cout<<"Closing inout file."<<endl;
    gzt_inout_file.seekp(inout_buf_start);
    gzt_inout_file.write(zbuf, inout_buf_size);
    return(1);
  }
  else return(-1);
}

