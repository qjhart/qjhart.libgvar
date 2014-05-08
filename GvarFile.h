#ifndef __GVARFILE_H
#define __GVARFILE_H

#include "Gvar.h"

#define GVNETBUFFSIZE 32768

namespace Gvar {
  class File : public IO {
  private:
	int fd;
	uint8_t blkbuf[GVNETBUFFSIZE];
	FILE* blkFile;

	// store the last block0 we have seen
	Gvar::Block0 *m_block0 ;

	// store the last frame id we have seen
	int m_prevFrameId ;

	void read_blkbuf_crc(int blkSz);
  public:
        File(std::string filename);
 
	~File();

	Gvar::Header* readHeader();
	void readVIPHeader();
        Gvar::Block* readBlock (Header* h) ;
        Gvar::Block* readBlock () ;
	void close();
	int eof();
	Gvar::Block0* getLastBlock0(void) {
		return m_block0;
	}
  };
}

#endif
