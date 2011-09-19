tinyurl is a bare bones url shortening tool written in C++ and bash script.
The redirects are handled by a C++ program (using FastCGI protocol) and
managing url's is done with the bash script.

I wrote this tool to see just how simple it would be to write the most basic
url shortener. There is nothing fancy going on here: long url's are stored
in files, minimal error handling (404 Not Found and 400 Bad Request), no hit
tracking.

I chose to write a raw CGI program instead of using a higher level scripting
language due to simplicity of the app. This also means that requirements are
simple; just a competent HTTP server capable of running FastCGI programs.


Building
========

- install [FastCGI](http://www.fastcgi.com/)
- modify `Makefile` settings as necessary (see *Buildtime settings*)
- run make
- copy `tinyurl.fcgi` to your web directory
- copy `tinyurl` script to somewhere in the path, eg: `~/bin`


Buildtime settings
==================

`Makefile` has a few settings that should be tweaked to suit your server:

- **SCRIPT_URL**: full url to `tinyurl.fcgi` (including trailing forward slash)
- **DATA_DIR**: directory where shortened url's are stored
- **TOKEN_LEN**: length of auto-generated url ID's


Apache settings
===============

Install and enable [mod_fcgid](http://httpd.apache.org/mod_fcgid/).

Optionally use the following `.htaccess` to rewrite all requests in a given
directory/location to the tinyurl.fcgi script. If tinyurl.fcgi is in a location
other than the root of the domain adjust the path in `ReweriteRule`
appropriately.

    Options +ExecCGI
    AddHandler fcgid-script .fcgi
    
    RewriteEngine On
    RewriteCond %{REQUEST_FILENAME} !-f
    RewriteRule ^(.*)$ /tinyurl.fcgi/$1 [L]
