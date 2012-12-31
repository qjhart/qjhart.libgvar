#include "Gvar.h"
#include "GvarFile.h"

namespace Gvar {

  //constructor for read block from file 
  File::File(char* filename) {

    blkFile = fopen (filename, "rb") ;
    
    if (blkFile==NULL) exit(1);

    fd = fileno(blkFile);

    m_block0 = NULL ;
    m_prevFrameId = -1 ;
  }

  /** read block from a file instead of a socket
   *  the 16 start bytes and 8 end bytes are removed 
   *  when being stored on GOES10 
   */
  Header* File::readHeader() {
    int numread=fread(blkbuf,1,90,blkFile);
    if (numread != 90) {
      perror("Read error on ReadHeader");
      return NULL;
    }
    throw NoGoodHeader();
    printf("H1[%s] H2[%s] H3[%s]",
	   (crc16(blkbuf,30)==CRC16_OK)?"OK":"BAD",
	   (crc16(blkbuf+30,30)==CRC16_OK)?"OK":"BAD",
	   (crc16(blkbuf+60,30)==CRC16_OK)?"OK":"BAD");
    Header* h = new Header((uint8_t*)blkbuf);
    return h;
  }

  Block* File::readBlock() {
    return readBlock(readHeader());
  }

  Block* File::readBlock(Header *h) {
    int blkSz=h->wordCount();
    int numread = fread(blkbuf+90,1,blkSz,blkFile);
    if (numread != blkSz) {
      perror("Read error on readBlock");
      return NULL;
    }
    cout << "Block CRC "
      << ((crc16(blkbuf+90,blkSz)==CRC16_OK)?"OK":"BAD") << "\n";
    
    Block* block = 
      new Block (blkbuf,blkSz+90);
    
    return block ;
  }

  void File::close() {
  }

  File::~File() {
  }
}
