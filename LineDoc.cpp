#include "Gvar.h"

namespace Gvar {
  LineDoc::LineDoc (Block* block) {
	Header* header = block->getHeader () ;
	int wordCount = header->wordCount () ;

	uint16_t* unpacked=new uint16_t[MAX_BLOCK_SZ];

	if ((((wordCount-2)*10/8)/5)*4 > MAX_BLOCK_SZ) 
	  throw linedoc_error();
	// "wordCount is too large: "<< wordCount<<">"<<(((MAX_BLOCK_SZ/4)*5)*8/10) + 2);
	
	// The value 'wordCount' means the number of words (10 bits each)
	// plus 2 (for CRC). So the number of bytes should be 
	// ((wordCount-2)*10)/8.
	
	// if ((wordCount-2)*10)%8 is not 0, then we get the invalid data
	/*if (((wordCount-2)*10)%8 != 0) {
	  printf ("The value in Word Count field does not match the data.") ;
	  //return ;
	  }*/
	
	unpack10 (block->getData (), ((wordCount-2)*10)/8, unpacked) ;
	
	Spcid = unpacked[0] ;
	Spsid = unpacked[1] ;
	Lside = unpacked[2] ;
	Lidet = unpacked[3] ;
	Licha = unpacked[4] ;
	RisctMsb  = unpacked[5] ;
	RisctLsb = unpacked[6] ;
	L1scan = unpacked[7] ;
	L2scan = unpacked[8] ;
	LpixlsMsb = unpacked[9] ;
	LpixlsLsb = unpacked[10] ;
	LwordsMsb = unpacked[11] ;
	LwordsLsb = unpacked[12] ;
	Lzcor  = unpacked[13] ;
	Llag   = unpacked[14] ;
	Lspar  = unpacked[15] ;
	
	int numOfPixels = ((int)LpixlsMsb << 10) + LpixlsLsb ;

	/* if numOfPixels is greater than (MAX_BLOCK_SZ-16),  this linedoc data does
	   not seem right. We ignore it here. */
	if (numOfPixels > MAX_BLOCK_SZ-16) {
	  //	  cerr << "LineDoc has size of "<< numOfPixels <<">"<<MAX_BLOCK_SZ-16;
	  throw linedoc_error();
	}
	
	data = new uint16_t[numOfPixels] ;
	for (int i=16; i<16+numOfPixels; i++) {
	  data[i-16] = unpacked[i] ;
	}

	delete[] unpacked ;
  }
 
  LineDoc::LineDoc(uint16_t* unpacked, int startpos) {
    int i = startpos;
    if(startpos+16 < MAX_BLOCK_SZ) {
      Spcid = unpacked[i] ;
      Spsid = unpacked[++i] ;
      Lside = unpacked[++i] ;
      Lidet = unpacked[++i] ;
      Licha = unpacked[++i] ;
      RisctMsb = unpacked[++i] ;
      RisctLsb = unpacked[++i] ;
      L1scan = unpacked[++i] ;
      L2scan = unpacked[++i] ;
      LpixlsMsb = unpacked[++i] ;
      LpixlsLsb = unpacked[++i] ;
      LwordsMsb = unpacked[++i] ;
      LwordsLsb = unpacked[++i] ;
      Lzcor = unpacked[++i] ;
      Llag = unpacked[++i] ;
      Lspar = unpacked[++i] ;

      int numOfPixels = ((int)LpixlsMsb << 10) + LpixlsLsb ;

      if (numOfPixels > MAX_BLOCK_SZ-startpos-16)
	throw linedoc_error();
      //cerr << "LineDoc has size of "<<numOfPixels<<" > "<<MAX_BLOCK_SZ-startpos-16;

      data = new uint16_t[numOfPixels] ;

      int k = 16 + startpos;
      for(int j = k; (j < k + numOfPixels) && (j < MAX_BLOCK_SZ); j++) {
        data[j-k] = unpacked[j] ;
      }
    } else {
      //      cerr<<"LineDoc does not have enough data:" <<endl;
      throw linedoc_error();
    }

  }//LineDoc(uint16_t*,int)

  LineDoc::~LineDoc () {
    delete[] data ;
  }
 
  void LineDoc::print( ostream & out ){ 
	
	out << "\n\t Line Documentation Definition" ; 
	
	out << "\n spcid : Spacecraft ID               " << spcid() ; 
	//	out << "\n\t " << SpaceCraftIDText[spcid() ];  
	
	out << "\n spsid : Sensor processing system ID " << spsid() ; 
	
	out << "\n lside : Active detector config ID   " << lside() ; 
	
	out << "\n lidet : Detector ID                 " << lidet() ; 
	
	out << "\n licha : Source channel ID           " << licha() ;
	//out << "\n\t" << SourceChannelIDText[licha()];
	
	out << "\n risct : Output scan count           " << risct() ; 
	
	out << "\n l1scan: Imager scan status (1)      " << l1scan() ; 
	
	out << "\n l2scan: Imager scan status (2)      " << l2scan() ; 
	
	out << "\n lpixls: Number of pixels in record  " << lpixls() ; 
	
	out << "\n lwords: Number of words in record   " << lwords() ; 
	
	out << "\n lzcor : Pixel offset employed at    ";
	out << "\n\t western edge of scan line   " << lzcor() ; 
	
	out << "\n llag  : Data lag ID                 " << llag() ; 
	
	out << "\n" ; 
	
  }
}
