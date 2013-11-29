#include "Header.h"
#include "Gvar.h"

#define WORD_COUNT_MIN 8040
#define WORD_COUNT_MAX 21008
#define WORD_SIZE_MAX 11
#define BLOCK_ID_MAX 12

namespace Gvar {
  Header::Header (uint8_t* header) {
    int goodStart;
    if (crc16(header,30)==CRC16_OK)
      goodStart=0;
    else if (crc16(header+30,30)==CRC16_OK)
      goodStart=30;
    else if (crc16(header+60,30)==CRC16_OK)
      goodStart=60;
    else
      throw no_good_header();
	
    BlockId = header[goodStart+0] ;
    WordSize = header[goodStart+1] ;
    WordCount= ( ((int)(header[goodStart+2]) <<8) +header[goodStart+3]) ;
    ProductId= ( ((int)(header[goodStart+4]) <<8) +header[goodStart+5]) ;
    RepeatFlag = header[goodStart+6] ;
    VersionNumber = header[goodStart+7] ;
    DataValid = header[goodStart+8] ;
    AsciiBin = header[goodStart+9] ;
    W11 = header[goodStart+10] ;
    RangeWord = header[goodStart+11] ;
    BlockCount = ( ((int)(header[goodStart+12]) <<8) +header[goodStart+13]) ;
    
    SpsTime.setTime(header+goodStart+16);
  }
  
  void Header::print( ostream & out ) {
    out << "\n\t Block Header "; 
    out << "\n Block Id " << blockId(); 
    out << "\n Word size " << wordSize() ; 
    out << "\n Word count " << wordCount() ; 
    out << "\n Product Id " << productId() ; 
    //	out << "\n\t" <<  ProductIDText[productID() ] ; 
    out << "\n Repeat flag " << repeatFlag() ; 
    out << "\n Version number " << versionNumber() ; 
    out << "\n Data Valid flag " << dataValid() ; 
    out << "\n ASCII / BIN data flag " << asciiBin() ; 
    out << "\n Range word " << rangeWord() ; 
    out << "\n Block count " << blockCount() ;
    out << "\n SPS Time" << SpsTime.getConcatenatedTime();
    out << "\n";
  }
}
