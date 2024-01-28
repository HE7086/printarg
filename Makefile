LTOFLAGS ?= -flto=auto -ffat-lto-objects 
CXXFLAGS ?= -std=c++23 -march=x86-64 -O2 -fno-plt -pipe \
			-fPIC -fstack-clash-protection -fcf-protection \
			-Wall -Wextra -Wpedantic -Werror \
			$(LTOFLAGS)
CPPFLAGS ?= -Wp,-D_FORTIFY_SOURCE=2,-D_GLIBCXX_ASSERTIONS
LDFLAGS ?= -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
LDLIBS ?= -lfmt -lstdc++

PREFIX ?= /usr/local

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

all: printarg

printarg: $(OBJECTS)
$(OBJECTS): %o: %cpp

.PHONY: install
install: printarg
	install -s -Dm755 $^ $(PREFIX)/bin/$^
	ln -sf $^ $(PREFIX)/bin/$^_hex

.PHONY: clean
clean:
	$(RM) printarg *.o
