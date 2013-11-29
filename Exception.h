#ifndef GVAR_EXCEPTION_H
#define GVAR_EXCEPTION_H

#include <boost/exception/all.hpp>
#include <iostream>
#include <stdexcept>

namespace Gvar {
  typedef boost::error_info<struct tag_bad_crc,int> bad_crc;

  struct file_read_error: virtual boost::exception, virtual std::exception { };
  struct crc_error: virtual boost::exception, virtual std::exception { }; 
  struct no_good_header: virtual boost::exception, virtual std::exception { }; 
  struct linedoc_error: virtual boost::exception, virtual std::exception { }; 

}

#endif //GVAR_EXCEPTION_H
