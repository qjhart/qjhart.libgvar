/* Read Gvar information 
*/

#include "GvarFile.h"
#include <stdlib.h>

using namespace Gvar;

int main(int argc, char* argv[]) {
  Gvar::File* gvar;
  gvar = new Gvar::File(argv[1]);
  Block0* m_block0;

  while (true) {
    Header* header = gvar->readHeader();
    if (header==NULL)
      break;
    header->print(cout);
    Block* block = gvar->readBlock(header);
    if (block == NULL)
      break;
    if (header->blockId() == 0) {
      m_block0 = new Block0 (block);
      Block0Doc* block0doc = m_block0->getBlock0Doc();
    }
  }
  gvar->close();
  delete gvar ;
  cout << "Done" <<endl;
  exit(EXIT_SUCCESS);
}
