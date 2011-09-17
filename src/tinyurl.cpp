#include "fcgi_io.h"
#include <string>
#include <fstream>

#ifndef LINKS_DIR
#  error LINKS_DIR is undefined, use Makefile to build
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
      // and I only want the first 4 characters
      std::string id(path.substr(1, 4));

      if (id.length() != 4) {
         // url ID was not the right length
         io << "Status: 400 Bad Request\r\n\r\n";
      } else {
         path = LINKS_DIR + ('/' + id);
         std::ifstream f(path.c_str());

         if (!f) {
            // file failed to open, 'Not Found'
            io << "Status: 404 Not Found\r\n\r\n";
         } else {
            std::string url;

            // file should contain single line which is URL
            std::getline(f, url);

            // send the redirect response
            io << "Status: 301 Moved Permanently\r\n";
            io << "Location: " << url << "\r\n\r\n";
         }
      }

      FCGX_Finish_r(&request);
   }

   return 0;
}

