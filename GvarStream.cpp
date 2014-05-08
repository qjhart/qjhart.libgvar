#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "Gvar.h"
#include "GvarStream.h"
#include "Block.h"

static unsigned char startpatt[8]={0xAA,0xD6,0x3E,0x69,0x02,0x5A,0x7F,0x55};
static unsigned char endpatt[8]={0x55,0x7F,0x5A,0x02,0x69,0x3E,0xD6,0xAA};

namespace Gvar {

  Stream::Stream(char *ipaddr,int port) {

    if ((this->ipaddr = (char *)malloc(strlen(ipaddr)+1)) == (void *) 0) {
      delete this;
    }
    strcpy(this->ipaddr,ipaddr);
    this->port=port;
    this->seqnum=0;
    this->bp = this->blkbuf;

    m_block0 = NULL ;

    m_prevFrameId = -1 ;
  }
 
  Stream::~Stream () {

    if (ipaddr != NULL) {
      delete ipaddr ;
    }

    if (m_block0 != NULL) {
      delete m_block0 ;
    }

    close () ;
  }

  int Stream::connect(void)
  {
	int fd;
	struct sockaddr_in sa;
	int optval;
	
	fd=socket(PF_INET,SOCK_STREAM,0);
	if (fd==-1) return(fd);
	memset(&sa,0,sizeof(sa));
	sa.sin_family=AF_INET;
	// inet_aton(host_p->h_addr_list[0],(in_addr *)&sa.sin_addr.s_addr);
	sa.sin_addr.s_addr=inet_addr(this->ipaddr);
	sa.sin_port=htons(this->port);
	if (::connect(fd,(struct sockaddr *)&sa,sizeof(sa))==-1) return -1;
	optval=1;
	// SCT added 8/4/03
	setsockopt(fd,SOL_SOCKET,SO_KEEPALIVE,&optval,sizeof(optval));
	// non-portable options that are required to speed up the keep-alive
	// process by default it will wait 2hrs! after idle before the fist keep alive
	// since this link must be over a fast network these values are justified
	// sets all three default parameters so nothing is left to some riduculous default
	optval=30;  // let it be idle for 30 seconds before sending a keep alive
	setsockopt(fd,SOL_TCP,TCP_KEEPIDLE,&optval,sizeof(optval));
	optval=2;   // go for two retries before error out
	setsockopt(fd,SOL_TCP,TCP_KEEPCNT,&optval,sizeof(optval));
	optval=15;  // fifteen seconds between retries
	setsockopt(fd,SOL_TCP,TCP_KEEPINTVL,&optval,sizeof(optval));
	return(fd);
  }

  bool Stream::listen (void)
  {
	this->fd=this->connect();
	this->seqnum=0;
	return (fd != -1) ;
  }

  int Stream::readBlkBuf () {
    unsigned int seqnum;

    int datalen = 16 ;
    int bp = 0 ;
    while(1) {
      numread=recv(fd, blkbuf+bp,datalen-bp, MSG_NOSIGNAL);
      if (numread<=0) {
	fprintf(stderr, "Read error") ; fflush (stderr) ;
	return 0;
      }
      bp+=numread;
      if (bp==16) {
        if (memcmp(blkbuf,startpatt,8)) {
	  fprintf (stderr, "Bad Start") ; fflush (stderr) ;
	  return 0;
	}
        datalen=ntohl(*((int*)(blkbuf+8)))+24;
        seqnum=ntohl(*((int*)(blkbuf+12)));
        if (seqnum!=this->seqnum+1) {
	  fprintf (stderr, "Bad Sequence:") ; fflush (stderr) ;
	}

        if (datalen>GVNETBUFFSIZE) {
	  fprintf (stderr, "Block Too Big") ; fflush (stderr) ;
	  return 0;
	}
        this->seqnum=seqnum;
        this->end=this->blkbuf+datalen;
      }
      if (bp==datalen) {
        if (memcmp(blkbuf+datalen-8,endpatt,8)) {
	  fprintf (stderr, "Bad End") ; fflush (stderr) ;
	  return 0;
	}
        break ;
      }
    }
    return datalen;
  }

  Header* Stream::readHeader () {
    int datalen;
    int blkSz;
    datalen=this->readBlkBuf();

    if (datalen < 90+16)
      return (Header *)NULL;

    Header *h=new Header(blkbuf+16);
    return h;
  }

  Block * Stream::readBlock(Header *h) {
    int blkSz=h->wordCount()*h->wordSize()/8;
    uint16_t crc=crc16(blkbuf+90+16,blkSz);
    // if (crc != CRC16_OK)
    //   std::cerr << "Bad CRC: " << crc;
    Block* block =  new Block (h, blkbuf+16+90,blkSz);    
    return block ;
  }

  Block* Stream::readBlock() {
    return readBlock(readHeader());
  }

  void Stream::close () {
    if (fd != -1) {
      shutdown (fd, SHUT_RD) ;
      fd = -1 ;
    }

  }
  
}

