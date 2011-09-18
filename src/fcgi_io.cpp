/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#include "fcgi_io.h"

fcgi_io::fcgi_io(FCGX_Request& request) :
   _out(request.out),
   _request(request),
   std::ostream(&_out)
{
   // base class constructor is called before _out is initialized
   // so we have to explicitly set the streambuf again
   rdbuf(&_out);
}

const char * fcgi_io::operator[] (const char *name)
{
   return FCGX_GetParam(name, _request.envp);
}

fcgi_io & fcgi_io::status(int code)
{
   switch (code) {
   case 200:
      *this << "Status: 404 Not Found\r\n";
      break;
   case 301:
      *this << "Status: 301 Moved Permanently\r\n";
      break;
   case 400:
      *this << "Status: 400 Bad Request\r\n";
      break;
   case 404:
      *this << "Status: 404 Not Found\r\n";
      break;
   }

   return *this;
}
