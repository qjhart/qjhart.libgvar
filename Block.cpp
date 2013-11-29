#include "Gvar.h"

namespace Gvar {

  Block::Block(Header *h, uint8_t* buff, int buff_size)
  {
    header=h;
    data = new uint8_t[buff_size] ; 
    memcpy (data, buff, buff_size) ;
  } 
  
  Block::~Block () {
    delete[] data ;
  }
  
  uint8_t* Block::getData()
  { return data ;}
  
  Header* Block::getHeader()
  {return header ;}
}
