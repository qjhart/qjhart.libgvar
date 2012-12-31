#ifndef GVAR_HEADER_H
#define GVAR_HEADER_H

#include <stdint.h>

  /* refer page 61, goes-i/m oge specs  */
#include "cdaTime.h"

#define HEADER_BSZ 30  

#define WORD_COUNT_MIN 8040
#define WORD_COUNT_MAX 21008
#define WORD_SIZE_MAX 11
#define BLOCK_ID_MAX 12

namespace Gvar {
  class Header{ 
  private:
	uint8_t BlockId;       // 1 
	uint8_t WordSize;      // 2 
	int WordCount;  // 3+4	
	uint16_t ProductId;  // 5+6
	uint8_t RepeatFlag;    // 7
	uint8_t VersionNumber; // 8
	uint8_t DataValid;     // 9
	uint8_t AsciiBin;      // 10
	uint8_t W11;           // 11
	uint8_t RangeWord;     // 12 
	uint16_t BlockCount; // 13+14
	CdaTime SpsTime; //16-24
	//	uint8_t W15_28[14];    // 15 28

  public:
	Header (uint8_t* header) ;
	
	uint16_t blockId();
	uint16_t wordSize();
	int wordCount();
	uint16_t productId();
	uint16_t repeatFlag();
	uint16_t versionNumber();
	uint16_t dataValid();
	uint16_t asciiBin();
	uint16_t rangeWord();
	uint16_t blockCount();
	uint16_t crc();
	int nBytes();
	
	void print(ostream & out) ; 
  };
  
  inline uint16_t Header::blockId() 
	{ return ( (BlockId)==240 ? 0: (BlockId) ) ; }
  
  inline uint16_t Header::wordSize() 
	{ return WordSize; } 
  
  inline int Header::wordCount() 
  { return WordCount;}
  
  inline uint16_t Header::productId() 
    { return ProductId;}
  
  inline uint16_t Header::repeatFlag()
	{ return RepeatFlag ; }
  
  inline uint16_t Header::versionNumber()
	{ return VersionNumber; }
  
  inline uint16_t Header::dataValid() 
	{ return DataValid ; }
  
  inline uint16_t Header::asciiBin() 
	{ return AsciiBin; }
  
  inline uint16_t Header::rangeWord() 
	{ return RangeWord; }
  
  inline uint16_t Header::blockCount() 
    { return BlockCount;}
  
  inline	int Header::nBytes() 
	{ return( wordSize() * wordCount() / 8 ); }
}  
#endif //HEADER
  

