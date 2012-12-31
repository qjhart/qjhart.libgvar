#ifndef GVAR_BLOCK_H
#define GVAR_BLOCK_H

#include <iostream>
#include "Header.h"
#include "Block0Doc.h"
#include "LineDoc.h"
using std::iostream ;
using std::ostream ;

namespace Gvar {
  class Block { 
  private:
	
	Header* header ;
	uint8_t* data;  // pointer to buffer for gvar data stream in memory
	
	Header* createHeader (uint8_t* buff) ;

	uint8_t* m_rawData ;
	int m_rawDataLen ;
	
  public:
	Block(uint8_t* buff, int buff_size); 
	~Block();
	uint8_t* getData();//Find block of data and copy contents to Data
	
	Header* getHeader () ; // Return the header

	// Return the gvar raw data for this block
	inline uint8_t* getRawData () {
	  return m_rawData ;
	}
	// Return the length of the gvar raw data for this block
	inline int getRawDataLen () {
	  return m_rawDataLen ;
	}
  };

  class Block0 {
  private:
    // the pointer to GvarBlock
    Block* block ;

    // the line document of the data
    Block0Doc* block0Doc ;

  public:
    //Block0 (Block* b):block(b), block0Doc(new Block0Doc(b)) {} ;
    Block0 (Block* b) ;
    ~Block0 () ;

    Block* getBlock () ;
    Block0Doc* getBlock0Doc ();
  };
  
  inline Block* Block0::getBlock () { return block ; }
  inline Block0Doc* Block0::getBlock0Doc () { return block0Doc ; }


  class Block1or2 {
  private:
    // the pointer to GvarBlock
    Block* block ;

    // the line document of the data
    LineDoc** lineDoc;  

    // the number of linedocs
    int numOfLineDocs ;

    // the pixel data
    //uint16_t* data[4] ;

  public:
    Block1or2 (Block*) ;
    ~Block1or2 () ;

    Block* getBlock () ;
    LineDoc* getLineDoc (int) ;
    uint16_t* getData (int) ;
    // uint16_t** getData () ;
    int getDataLen (int) ;
    int getNumLineDocs () ;
  };

  inline Block* Block1or2::getBlock () { return block ; }
  inline LineDoc* Block1or2::getLineDoc (int i) { return lineDoc[i] ; }
  inline int Block1or2::getNumLineDocs () { return numOfLineDocs ; } 
 
  class Block3to10 {	
  private:
    // the pointer to GvarBlock
    Block* block ;
	
    // the line document of the data
    LineDoc* lineDoc ;
	
    // the pixel data
    uint16_t* data ;
	
    // the number of pixels in data
    int dataLen ;
	
  public:
    Block3to10 (Block*) ;

    ~Block3to10 () ;
	
    Block* getBlock () ;
    LineDoc* getLineDoc () ;
    uint16_t*  getData () ;
    int getDataLen () ;
  } ;
  
  inline Block* Block3to10::getBlock () { return block ; }
}
#endif // GVAR_H
  

