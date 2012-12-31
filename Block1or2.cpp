/**
 * This file defines the functions for the class.
 */
#include "Gvar.h"

namespace Gvar {
  Block1or2::Block1or2 (Block* block) {
    this->block = block ;

    Header* gvarHeader = block->getHeader() ;
    uint16_t blockID = gvarHeader->blockId() ;

    int wordcount = gvarHeader->wordCount() ;
    uint16_t* unpacked = new uint16_t[MAX_BLOCK_SZ] ;
    unpack10(block->getData(), ((wordcount - 2) * 10)/8, unpacked) ;

    int Pixels = 0;
    int temp = 0;
    
    //mbbyrd 12/2011
    //with gvar version P, block 2 now has 4 line docs too
    numOfLineDocs = 4;
    // if(blockID == 1) {
    //   numOfLineDocs = 4 ;
    // } else {
    //   numOfLineDocs = 3 ;
    // }

    lineDoc = new LineDoc*[numOfLineDocs] ;

    //added by mb 12.2011
    for (int l = 0; l < numOfLineDocs; ++l){
      lineDoc[l] = NULL;
    }


    for(int i = 0; i < numOfLineDocs; ++i) {
      lineDoc[i] = new LineDoc(unpacked, temp) ;
      Pixels = lineDoc[i]->lwords() ;
      temp += Pixels ;
    }

    delete [] unpacked ;
  }//Block1or2(Block*)
 
  Block1or2::~Block1or2 () {
    int blockID = block->getHeader()->blockId() ; 

    for (int lineDocNo=0; lineDocNo<numOfLineDocs; lineDocNo++) {
      delete lineDoc[lineDocNo] ;
    }
    delete[] lineDoc ;
  }//~Block1or2()

  uint16_t* Block1or2::getData(int i) {
    return lineDoc[i]->getData();
  }
 
//   uint16_t** Block1or2::getData() {
//     uint16_t** data;
//     data = new (uint16_t*)[numOfLineDocs];
//     for(int i=0; i<numOfLineDocs; i++) {
//       data[i] = lineDoc[i]->getData();
//     }
//     return data;
//   }

  int Block1or2::getDataLen(int i) {
    return lineDoc[i]->lpixls();
  }

}//namespace Gvar
