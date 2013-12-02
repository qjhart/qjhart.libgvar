#include "Gvar.h"

namespace Gvar {

  Block::Block(Header *h, uint8_t* buff, int buff_size)
  {
    header=h;
    datalen=buff_size;
    data = new uint8_t[buff_size] ; 
    memcpy (data, buff, buff_size) ;
  } 
  
  Block::~Block () {
    delete[] data ;
  }
  
  //  uint8_t* Block::getData()
  //{ return data ;}
  bool Block::crc16_ok() {
    return (crc16(data,datalen)==CRC16_OK);
  }
  
  uint8_t* Block::getRawData()
  { return data ;}
  
  int Block::getRawDataLen()
  { return datalen;}
  
  Header* Block::getHeader()
  {return header ;}
}
