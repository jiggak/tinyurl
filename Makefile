# URL where tinyurl is installed, used by shell script only
SCRIPT_URL=http://0x2a.ca/

# directory where URL files are stored
DATA_DIR=/home/web/0x2a.ca/links

# number of characters used to generate URL tokens
TOKEN_LEN=3

CXX=g++
CXXFLAGS=-Wall -DDATA_DIR=\"$(DATA_DIR)\" -DTOKEN_LEN=$(TOKEN_LEN)
LDFLAGS=-lfcgi++

all: tinyurl.fcgi tinyurl

tinyurl: tinyurl.in
	@sed 's/@DATA_DIR@/$(subst /,\/,$(DATA_DIR))/' tinyurl.in | \
	     sed 's/@TOKEN_LEN@/$(TOKEN_LEN)/' | \
	     sed 's/@SCRIPT_URL@/$(subst /,\/,$(SCRIPT_URL))/' > tinyurl
	@chmod +x tinyurl

tinyurl.fcgi: src/tinyurl.o src/fcgi_io.o
	$(CXX) -o $@ $(LDFLAGS) $^

.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@rm src/*.o tinyurl.fcgi tinyurl
