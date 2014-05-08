/* Read Gvar information 
*/
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <iostream>
#include <iterator>

using namespace std;

#include "Gvar.h"
#include <stdlib.h>

using namespace Gvar;

int main(int ac, char* av[]) {
  std::string file;
  int port;
  std::string ip;
  bool vip=false;
  Gvar::IO* gvar;

  try {
    po::options_description desc("Allowed options");
    desc.add_options()
      ("help", "produce help message")
      ("vip", "Automated Sciences VIP format")
      ("file", po::value<string>(), "input file")
      ("ip",po::value<string>(&ip),"input IP Address")
      ("port",po::value<int>(&port)->default_value(21009),"Input port")
      //      ("file", po::value< vector<string> >(), "input files")
      ;
    po::positional_options_description p;
    p.add("file", -1);
    po::variables_map vm;
        po::store(po::command_line_parser(ac, av).
		  options(desc).positional(p).run(), vm);
    //    po::store(po::parse_command_line(ac, av, desc),vm);
    po::notify(vm);

    if (vm.count("help")) {
      cout << desc << "\n";
      return 1;
    }
    if (vm.count("vip")) {
      vip=true;
    }
    if (vm.count("file")==0) {
      if (vm.count("ip")==0) {
	cout << "No Input specified" <<endl <<desc << endl;
	return 1;
      } else {
	
	ip=vm["ip"].as<string>();
	port=vm["port"].as<int>();
	cout << "Using IP " << ip << " and port " << port;
	Gvar::Stream * gvars = new Gvar::Stream((char *)ip.c_str(),port);
	gvars->listen();
	gvar=gvars;
      }
    } else {
      file=vm["file"].as<string>();
      Gvar::File *gvarf = new Gvar::File(file);
      if(vip) {
	gvarf->readVIPHeader();
      }
      gvar=gvarf;
    }
  }
   catch(exception & e) {
    cerr << "error: " << e.what() << "\n";
    return 1;
  }
  catch(...) {
    cerr << "Exception of unknown type!\n";
  }
  
  Block0* m_block0;


  int count = 0;
  while (true) {
    cout << "HEADER: "<<++count << endl;
    Header* header = gvar->readHeader();
    if (header==NULL)
      break;
    header->print(cout);
    Block *block;
    cout << "BLOCK:"<<count << endl;
    block = gvar->readBlock(header);
    if (header->blockId() == 0) {
      m_block0 = new Block0 (block);
      Block0Doc* block0doc = m_block0->getBlock0Doc();
      block0doc->print(cout);
    } else if (header->blockId () == 1 || 
           header->blockId () == 2) {
      Block1or2* block1or2 = new Block1or2 (block) ;
      uint16_t* data;
      LineDoc* lineDoc;
      int numLines;
      numLines = block1or2->getNumLineDocs();
      cout << "numLineDocs: "<<numLines;

      for(int i=0; i<numLines; i++) {
        data = block1or2->getData(i) ;
        lineDoc = block1or2->getLineDoc(i) ;
	lineDoc->print(cout);
	//	if(lineDoc->licha() >= 2 && lineDoc->licha() <= 6 ) {
	// writeDataToChannel (lineDoc->licha()-1, data, 
	//			      block1or2->getDataLen(i)) ;
	//	}
      }
    }// end else if block 1-2
    else if (header->blockId () >= 3 && 
	     header->blockId () <= 10) {
      Block3to10* block3to10 = new Block3to10 (block) ;
      uint16_t* data;
      LineDoc* lineDoc;
      
      data = block3to10->getData();

      lineDoc = block3to10->getLineDoc() ;
      lineDoc->print(cout);
      //	if(lineDoc->licha() == 1) {
	//  if((lineDoc->lidet() >= 1) && (lineDoc->lidet() <= 8)) {
	//    writeDataToChannel (lineDoc->licha()-1, data, 
	//				block3to10->getDataLen()) ;
	//	}
	// }//if
    } // end else if block 3-10
    else { // skip other blocks
    }
    cout << "EOF:"<<gvar->eof();
    if (gvar->eof())
      break;
  }
  gvar->close();
  delete gvar ;
  exit(EXIT_SUCCESS);
}
