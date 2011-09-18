/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#ifndef FCGI_IO_H_
#define FCGI_IO_H_

#include <ostream>
#include <fcgio.h>

///
/// C++ ostream subclass for writing to FastCGI output stream and convenience
/// methods for setting HTTP response code and accessing CGI variables.
///
class fcgi_io : public std::ostream {
private:
   fcgi_streambuf _out;
   FCGX_Request& _request;

public:
   fcgi_io(FCGX_Request& request);

   /// Get the value of a CGI environment variable
   /// @param name environment variable name, eg: PATH_INFO
   /// @return value of variable, or NULL if not found
   const char * operator[] (const char *name);

   /// Print HTTP status line
   /// @param code HTTP status code
   /// @return this instance
   fcgi_io & status(int code);
};

#endif
