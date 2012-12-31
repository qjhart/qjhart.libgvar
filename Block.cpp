#include "Gvar.h"

namespace Gvar {
  Header* Block::createHeader (uint8_t* buff) {
	
    uint8_t temp[30] ;
    memcpy (temp, buff, 30) ;

    Header* header = new Header (temp) ;

    return header ;
  }
  
  
  Block::Block(uint8_t* buff, int buff_size)
  {

    m_rawDataLen = buff_size ;
    m_rawData = new uint8_t[m_rawDataLen] ; // (char*)malloc (m_rawDataLen) ;
    memcpy (m_rawData, buff, m_rawDataLen) ;

    header = createHeader (buff) ;
	
    // delete the first 3 30 bytes
    data = new uint8_t[buff_size-90] ;
    for (int i=90; i<buff_size; i++) {
      data[i-90] = buff[i] ;
    }
  } 
  
  Block::~Block () {
    delete[] data ;
    delete header ;

    delete[] m_rawData ;
  }
  
  uint8_t* Block::getData()
  { return data ;}
  
  Header* Block::getHeader()
  {return header ;}
}
