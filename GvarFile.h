#ifndef __GVARFILE_H
#define __GVARFILE_H

#include "LineDoc.h"
#include "Block.h"
#include "Exception.h"
#include <stdlib.h>

#define GVNETBUFFSIZE 32768
#define NUM_OF_CHANNELS 6

namespace Gvar {

  /*
    OLD GVAR Version I-L
  static const char* channelsDesc[NUM_OF_CHANNELS] = {
    "Channel 1, 0.52-0.75microns - cloud cover",
    "Channel 2,   3.8-4.0microns - night cloud cover",
    "Channel 3,   6.4-7.0microns - water vapor",
    "Channel 4, 10.2-11.2microns - sea surface temp.",
    "Channel 5, 11.5-12.5microns - sea surface temp."
  } ;

  static const int xRes[NUM_OF_CHANNELS] = {1,4,4,4,4} ;
  static const int yRes[NUM_OF_CHANNELS] = {1,4,8,4,4} ;
  */

  // GOES Version O-Beyond
  static const char* channelsDesc[NUM_OF_CHANNELS] = {
    "Channel 1, 0.52-0.75 microns - cloud cover",
    "Channel 2,   3.8-4.0 microns - night cloud cover",
    "Channel 3,   6.4-7.0 microns - water vapor",
    "Channel 4, 10.2-11.2 microns - sea surface temp.",
    "Channel 5, 11.5-12.5microns - sea surface temp."
    "Channel 6, 13.3 microns - sea surface temp."
  } ;

  static const int ew_res[NUM_OF_CHANNELS] = {1,4,4,4,4,4} ;
  static const int ns_res[NUM_OF_CHANNELS] = {1,4,4,4,4,4} ;

  static char startpatt[8]={0xAA,0xD6,0x3E,0x69,0x02,0x5A,0x7F,0x55};
  static char endpatt[8]={0x55,0x7F,0x5A,0x02,0x69,0x3E,0xD6,0xAA};

  class File {
  private:
	int fd;
	uint8_t blkbuf[GVNETBUFFSIZE];
	FILE* blkFile;

	// store the last block0 we have seen
	Gvar::Block0 *m_block0 ;

	// store the last frame id we have seen
	int m_prevFrameId ;

  public:
        File(char* filename);
 
	~File();

	Gvar::Header* readHeader();
        Gvar::Block* readBlock (Header* h) ;
        Gvar::Block* readBlock () ;
	void close();
	Gvar::Block0* getLastBlock0(void) {
		return m_block0;
	}
  };
}

#endif
