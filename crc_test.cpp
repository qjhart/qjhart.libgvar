/**************************************************************************
//
// main() - test driver for crc16 function
//
**************************************************************************/

#include "Gvar.h"
#include <stdlib.h>
#include <stdio.h>

using namespace Gvar;

int main(int argc, char* argv[]) {

  unsigned short crc;
  static char str[40];
  str[0] = 'T';
  str[1] = 0x04;
  str[2] = 0x7E;

  static char gvar[30]={
0xf0,0x08,0x1f,0x6a,0x00,0x03,0x01,0x03,0x01,0x00,
0x01,0xf0,0xa7,0x30,0x00,0x00,0x20,0x12,0x24,0x30,
0x10,0x05,0x54,0x17,0x00,0x00,0x00,0x00,0xec,0x06 };

  uint16_t_t test=crc16(gvar,30);
  printf ("crc(\"T\",2) = 0x%X\n",crc16(str,1));
  printf ("crc(\"T 0x04 0x7E\",3)=0x%X\n",crc16(str,3));
  printf("crc16(gvar,28) is 0x%X. crc16(gvar,30) is 0x%X (%s).\n",
	 crc16(gvar,28),
	 crc16(gvar,30),
  	 (crc16(gvar,30) == CRC16_OK)?"OK":"FAIL");
}

