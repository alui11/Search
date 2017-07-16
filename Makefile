CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu11
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	search

all:		$(TARGETS)

search: execute.o filter.o main.o search.o utilities.o
	@echo "Linking $@..."
	@$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c search.h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

test:		search test_search.sh
	@echo Testing $<...
	@./test_search.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o *.log *.input

.PHONY:		all test benchmark clean

# TODO: Add rules for search and object files
