/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#include "fcgi_io.h"
#include <string>
#include <fstream>

#ifndef DATA_DIR
#  error DATA_DIR is undefined, use Makefile to build
#endif

#ifndef TOKEN_LEN
#  error TOKEN_LEN is undefined, use Makefile to build
#endif


int main()
{
   FCGX_Request request;

   FCGX_Init();
   FCGX_InitRequest(&request, 0, 0);

   while (FCGX_Accept_r(&request) == 0) {
      fcgi_io io(request);

      // PATH_INFO contains everything in the URL after the script
      // eg: myscript.cgi/this/is/path/info
      std::string path(io["PATH_INFO"]);

      // path will always begin with a '/' so skip it
      // and I only want the number of characters defined as token length
      std::string token(path.substr(1, TOKEN_LEN));

      if (token.length() != TOKEN_LEN) {
         // url token was not the right length
         io.status(400) << "Content-Type: text/plain\r\n\r\n";
         io << "url tokens must be " << TOKEN_LEN << " characters long";
      } else {
         path = DATA_DIR + ('/' + token);
         std::ifstream f(path.c_str());

         if (!f) {
            // file failed to open, 'Not Found'
            io.status(404) << "Content-Type: text/plain\r\n\r\n";
            io << "url token does not exist";
         } else {
            std::string url;

            // file should contain single line which is URL
            std::getline(f, url);

            // send the redirect response
            io.status(301) << "Location: " << url << "\r\n\r\n";
         }
      }

      FCGX_Finish_r(&request);
   }

   return 0;
}
