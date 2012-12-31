#ifndef GVAR_EXCEPTION_H
#define GVAR_EXCEPTION_H

#include <iostream>
#include <stdexcept>

using std::runtime_error;
namespace Gvar {
  class CRCException : public runtime_error {
  public:
    CRCException(): runtime_error("CRC Check Failure") {}
  };
  class NoGoodHeader: public runtime_error {
  public:
  NoGoodHeader(): runtime_error("No good Header for Block"){}
  };
}

#endif //GVAR_EXCEPTION_H
