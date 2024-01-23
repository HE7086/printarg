CXX ?= g++
CXXFLAGS ?= -std=c++23 -march=x86-64-v3 -O2 -flto -ffat-lto-objects -s \
			-fPIC -fstack-clash-protection -fcf-protection \
			-Wp,-D_FORTIFY_SOURCE=2,-D_GLIBCXX_ASSERTIONS
LDFLAGS ?= -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
LDLIBS ?= -lfmt
PREFIX ?= /usr/local

all: printarg

printarg.o: printarg.cpp
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(LDFLAGS) -o $@ -c $^

printarg: printarg.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(LDFLAGS) -o $@ $^

install: printarg
	install -Dm755 printarg $(PREFIX)/bin

.PHONY: clean
clean:
	rm -f printarg *.o
