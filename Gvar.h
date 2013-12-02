#ifndef GVAR_H
#define GVAR_H

#include <boost/format.hpp>

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "LineDoc.h"
#include "Block.h"
#include "Exception.h"

#ifndef BUFSIZ 
#define BUFSIZ 4096
#endif

#ifndef FILENAME_SIZE
#define FILENAME_SIZE 1024
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define ALL -1

#define CRC16_OK 0xE2F0

#define GVARBUFSIZ  BUFSIZ  
#define MAX_BLOCK_SZ  52348 

#define INSTRUMENTS 2

#define MAX_FRAMES 64
#define MAX_ARGS 2048

#define ICHANNELS 5
#define SCHANNELS 19
#define CHANNELS SCHANNELS

#define SSIDES 1
#define ISIDES 2
#define SIDES ISIDES

#define IDETECTORS 8 
#define SDETECTORS 4
#define DETECTORS IDETECTORS

#define IMAGERMAXCOUNTS ((1<<10)-1)
#define SOUNDERMAXCOUNTS ((1<<16)-1)

#define SPIXELS 11

static const int MAXCOUNTS[] = { IMAGERMAXCOUNTS, SOUNDERMAXCOUNTS};

static const char * SpaceCraftIDText[] = { 
	" 0 ",
	" 1 ",
	" 2 ",
	" 3 ", 
	" 4 ",
	" 5 ", 
	" 6 ",
	" 7 ",
	" 8 GOES-I ",
	" 9 GOES-J ",
	"10 GOES-K ",
	"11 GOES-L ",
	"12 GOES-M ",
	"13 GOES-N ",
	"14 GOES-O ",
	"15 GOES-P ",
	"16 GOES-Q "
};

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

/* //skip factors for channels */
/* static const int IVISPXLS[INSTRUMENTS][CHANNELS] ={  */
/*   {1,4,4,4,4},  */
/*   {1,1,1,1,1, */
/*    1,1,1,1,1, */
/*    1,1,1,1,1, */
/*    1,1,1,1 }  }; */

/* static const int IVISLINS[INSTRUMENTS][CHANNELS]={ */
/*   {1,4,8,4,4}, */
/*   {1,1,1,1,1, */
/*    1,1,1,1,1, */
/*    1,1,1,1,1, */
/*    1,1,1,1 }  }; */

// Imager & sounder constants

/* static const int Channel[INSTRUMENTS] = { ICHANNELS, SCHANNELS}; */
/* static const int Detector[INSTRUMENTS][CHANNELS]= */
/* {{ 8,2,1,2,2 },  */
/*  { 4,4,4,4,4, */
/*    4,4,4,4,4, */
/*    4,4,4,4,4, */
/*    4,4,4,4} }; */

/* static const int Side[INSTRUMENTS][CHANNELS] = */
/* { {2,2,2,2,2}, */
/*   {1,1,1,1,1, */
/*    1,1,1,1,1, */
/*    1,1,1,1,1, */
/*    1,1,1,1 } }; 	 */

inline int VALID(int a, int b) { return ((a==-1)?(b):(a)) ; } 

#define NUM_OF_CHANNELS 6

namespace Gvar {

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

  class LineDoc;
  class Block;
  class Header;
  class Block0Doc;
  class Block0;
  class Block1or2;
  class Block3to10;
  // This function converts every 10 bits of a byte array to 16 bits.
  void unpack10 (uint8_t*, int, uint16_t*) ;

  uint16_t crc16(uint8_t* ptr,uint16_t len);
}

#include "Block.h"
#include "LineDoc.h"
#include "Block0Doc.h"
#include "Exception.h"
#include "GvarFile.h"
#include "GvarStream.h"

#endif // GVAR_H
  

