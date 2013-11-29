#ifndef __GEOSTREAM_GVARSTREAM_H
#define __GEOSTREAM_GVARSTREAM_H

#include "Gvar.h"

#define GVNETBUFFSIZE 32768
#define NUM_OF_CHANNELS 6

namespace Gvar {

  class Stream {
  private:
	unsigned int seqnum;
	char *ipaddr;
	int port;
	int fd;
	int numread;
	uint8_t *bp;
	uint8_t *end;
	uint8_t blkbuf[GVNETBUFFSIZE];

	// store the last block0 we have seen
	Gvar::Block0 *m_block0 ;

	// store the last frame id we have seen
	int m_prevFrameId ;

	int connect(void);

  public:
	Stream(char *ipaddr,int port);

        Stream(char* filename);
 
	~Stream();
	bool listen(void);

	void close () ;

        Gvar::Block* readBlock () ;

  };
}

#endif
