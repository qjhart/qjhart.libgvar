#include "Gvar.h"
#include "GvarFile.h"

namespace Gvar {

  //constructor for read block from file 
  File::File(std::string filename) {

    blkFile = fopen (filename.c_str(), "rb") ;
    
    if (blkFile==NULL) exit(1);

    fd = fileno(blkFile);

    m_block0 = NULL ;
    m_prevFrameId = -1 ;
  }

  /** VIP files have this wierd header, I haven't decoded */
  void File::readVIPHeader() {
    fseek(blkFile,606500,SEEK_SET);
  }

  int File::eof() {
    return feof(blkFile);
  }

  /** read block from a file instead of a socket
   */
  Header* File::readHeader() {
    if (fread(blkbuf,1,90,blkFile) != 90)
      return (Header *)NULL;
      //      throw Gvar::file_read_error() << boost::errinfo_errno(errno);

    /*
        printf("H1[%0x,%s] H2[%s] H3[%s]",
	   crc16(blkbuf,30),(crc16(blkbuf,30)==CRC16_OK)?"OK":"BAD",
	   (crc16(blkbuf+30,30)==CRC16_OK)?"OK":"BAD",
	   (crc16(blkbuf+60,30)==CRC16_OK)?"OK":"BAD");
    */
    Header* h = new Header((uint8_t*)blkbuf);
    return h;
  }

  Block* File::readBlock() {
    return readBlock(readHeader());
  }

  void File::read_blkbuf_crc(int blkSz) {
    if (blkSz != fread(blkbuf,1,blkSz,blkFile))
      1; // throw file_read_error() << boost::errinfo_errno(errno);

    uint16_t crc=crc16(blkbuf,blkSz);
        if (crc != CRC16_OK) 
	  1; //throw crc_error() << bad_crc(crc);
  }

  Block* File::readBlock(Header *h) {
    int blkSz=h->wordCount()*h->wordSize()/8;
    try {
      File::read_blkbuf_crc(blkSz);
          } catch ( no_good_header & x ) {
      std::cerr << "Block CRC Error";
      if ( int const * mi=boost::get_error_info<bad_crc>(x) )
      	std::cerr << " Bad CRC: " << *mi;
      std::cerr << endl;
    }
    
    //    printf("Block CRC:%0x %s\n",crc16(blkbuf,blkSz),
    //	   (crc16(blkbuf,blkSz)==CRC16_OK)?"OK":"BAD");
    
    Block* block =  new Block (h, blkbuf,blkSz);
    
    return block ;
  }

  void File::close() {
  }

  File::~File() {
  }
}
