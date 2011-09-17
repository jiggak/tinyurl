LINKS_DIR=/home/josh/.tinyurl

CXX=g++
CXXFLAGS=-Wall -g -DLINKS_DIR=\"$(LINKS_DIR)\"
LDFLAGS=-lfcgi++

tinyurl.fcgi: src/tinyurl.o src/fcgi_io.o
	$(CXX) -o $@ $(LDFLAGS) $^

.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@rm src/*.o tinyurl.fcgi
