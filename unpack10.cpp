#include "Gvar.h"

  // This function converts every 10 bits of a byte array into 16 bits.
void Gvar::unpack10 (uint8_t* in,
					 int len,
					 uint16_t* out) {
  // We notice that every 5 bytes (40 bits) of 'in' will be converted
  // to 4 16-bits. So I will try to put 4 bytes into a 'uint32_t' value
  // and 1 byte in a 'uint8_t' value.
  uint32_t fourBytes ;
  uint8_t oneByte ;
  
  // the index for the output string
  int outIndex = 0 ;
  for (int i=0; i<=len-5; i+=5) {
	fourBytes = (in[i]<<24) + (in[i+1]<<16) + (in[i+2]<<8) + in[i+3] ;
	oneByte = in[i+4] ;
	
	uint32_t temp = fourBytes >> 22 ;
	out[outIndex++] = (uint16_t)temp ;
	
	temp = (fourBytes << 10) >> 22 ;
	out[outIndex++] = (uint16_t)temp ;
	
	temp = (fourBytes << 20) >> 22 ;
	out[outIndex++] = (uint16_t)temp ;
	
	temp = ((fourBytes << 30) >> 22) + oneByte ;
	out[outIndex++] = (uint16_t)temp ;
	
  }
}

