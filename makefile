CC = gcc

SPATH = src
OPATH = obj
BPATH = bin
HPATH = include
DPATH = doc
TPATH = tests

CFLAGS = -std=gnu99 -pedantic -Werror -W -Wall -Wextra -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual
IFLAGS = -I$(HPATH) -I$(TPATH)
LFLAGS = -L/usr/lib -L/usr/lib64

vpath %.c $(SPATH)/ $(TPATH)/
vpath %.h $(HPATH)/ $(TPATH)/
vpath %.o $(OPATH)/

all: anna-lise

anna-lise: main.o | bin
		$(CC) $(CFLAGS) -o $(BPATH)/$@ $(OPATH)/main.o $(LFLAGS)

tests: tests.o test_base.o test_icmp_util.o icmp_util.o | bin
		$(CC) $(CFLAGS) -o $(BPATH)/$@ $(OPATH)/tests.o $(OPATH)/test_base.o $(OPATH)/test_icmp_util.o $(OPATH)/icmp_util.o $(LFLAGS) -lcunit

%.o: %.c | obj
		$(CC) $(CFLAGS) -o $(OPATH)/$@ -c $< $(IFLAGS)

# Anna-lise
main.o: main.c base.h
icmp_util.o: icmp_util.c icmp_util.h base.h

# Tests
tests.o: tests.c CUnit_util.h
test_base.o: test_base.c test_base.h CUnit_util.h base.h
test_icmp_util.o: test_icmp_util.c test_icmp_util.h CUnit_util.h base.h icmp_util.h

doc: cleandoc
		@doxygen
obj:
		@mkdir -p $(OPATH)

bin:
		@mkdir -p $(BPATH)

clean:
		@rm -rf $(OPATH) $(BPATH)

cleandoc:
		@rm -rf $(DPATH)

cleanall: clean cleandoc
		@echo "Clean."

archive:
		@tar -cvzf $(shell basename `pwd).tar.gz $(SPATH) $(HPATH) makefile Doxyfile AUTHORS COPYING LICENSE README README.md
