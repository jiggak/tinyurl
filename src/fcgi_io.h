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

class fcgi_io : public std::ostream {
private:
   fcgi_streambuf _out;
   FCGX_Request& _request;

public:
   fcgi_io(FCGX_Request& request);

   const char * operator[] (const char *name);
};

#endif
