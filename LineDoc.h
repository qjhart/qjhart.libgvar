#ifndef LINE_DOC_H
#define LINE_DOC_H

#include <stdint.h>

#define IMAGER_LINES_MAX 1974
#define LINEDOC_BSZ 32

#include <iostream>
using std::iostream ;
using std::ostream ;

namespace Gvar {

  class Block ;

  class LineDoc{ 
  private: 
	uint16_t Spcid; //1 
	uint16_t Spsid; // 2
	uint16_t Lside; // 3
	uint16_t Lidet; // 4
	
	
	uint16_t Licha; // 5
	uint16_t RisctMsb ; // 6 
	uint16_t RisctLsb; // 7 
	
	uint16_t L1scan;   //8
	uint16_t L2scan;   //9
	
	uint16_t LpixlsMsb; // 10 
	uint16_t LpixlsLsb; // 11
	
	uint16_t LwordsMsb; // 12 
	uint16_t LwordsLsb; // 13
	
	uint16_t Lzcor ;    // 14 
	uint16_t Llag  ;    // 15 
	uint16_t Lspar ;    // 16 
	
	// the data
	uint16_t* data ;
	
  public: 
	LineDoc(Block* block) ; 
	LineDoc(uint16_t* unpacked, int startpos) ;
	~LineDoc () ;
	
	int spcid() { return( Spcid ); }
	int spsid() { return( Spsid ); }
	int lside() { return( Lside ); }
	int lidet() { return( Lidet ); }
	int licha() { return( Licha ); }
	uint16_t risct() {return(((uint16_t)RisctMsb<<10)+RisctLsb ); }
	int l1scan() { return( L1scan ) ; }
	int l2scan() { return( L2scan ) ; }
	int lpixls() { return( ((int)LpixlsMsb << 10) + LpixlsLsb ); } 
	int lwords() { return( ((int)LwordsMsb << 10) + LwordsLsb ); } 
	int lzcor() { return( Lzcor ); }
	int llag() { return( Llag ); }
	
	int channel() { return (Licha -1) ; }
	
	int detector(){ return( (Licha == 1) ? (Lidet+3)&7 : (Lidet-1)&1); }
	// channel	logical det	normal Lidet	flip Lidet
	// visible: norm: det = (Lidet+3)&7  flip: det = (12-Lidet)&7
	//	1	0		5		4
	//	1	1		6		3
	//	1	2		7		2
	//	1	3		8		1
	//	1	4		1		8
	//	1	5		2		7
	//	1	6		3		6
	//	1	7		4		5
	// infrared: norm: det = (Lidet-1)&1  flip: det = (chan 3: 0, others: Lidet&1)
	//	2	0		5		6
	//	2	1		6		5
	//	3	0		7		7
	//	4	0		1		2
	//	4	1		2		1
	//	5	0		3		4
	//	5	1		4		3
	// BUT: the flip bit (bit 16 of Iscan) is not included with linedoc data so
	//      I modify Lidet in the case of flip mode so that the above function
	//      will return the correct logical detector value.
	// visible: Lidet = (det+4)&7+1 = (9-Lidet) where det is the block number - 3
	// infrared: Lidet = (2*c+d)%8+1 where c=channel, d=expected detector
	// see gvar.C, list.C for more details 
	
	int side() { return((Lside)?1:0); }
	
	uint16_t* getData () { return data ; }
	
	LineDoc* next() { return (LineDoc*) ( (uint16_t*) this + lwords() ) ; }
	
	int valid();  
	void print( ostream & ) ; 
	
	int bytes(); 
	
  }; 
  
  inline int LineDoc::valid() {
	return (lpixls() < lwords() ) ; }
  
  inline int LineDoc::bytes() { return(lwords()*10/8); }  
}
#endif


