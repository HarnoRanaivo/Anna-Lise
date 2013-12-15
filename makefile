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

tests: unit_tests other_tests

unit_tests: unit_tests.o test_base.o test_icmp_util.o icmp_util.o test_ip_util.o ip_util.o test_checksum.o checksum.o test_packet.o packet.o address.o | bin
	$(CC) $(CFLAGS) -o $(BPATH)/unit_tests $(OPATH)/unit_tests.o $(OPATH)/test_base.o $(OPATH)/test_icmp_util.o $(OPATH)/icmp_util.o $(OPATH)/ip_util.o $(OPATH)/test_ip_util.o $(OPATH)/test_checksum.o $(OPATH)/checksum.o $(OPATH)/test_packet.o $(OPATH)/packet.o $(OPATH)/address.o $(LFLAGS) -lcunit

other_tests: test_address | bin

test_address: test_address.o address.o | bin
	$(CC) $(CFLAGS) -o $(BPATH)/test_address $(OPATH)/test_address.o $(OPATH)/address.o

%.o: %.c | obj
		$(CC) $(CFLAGS) -o $(OPATH)/$@ -c $< $(IFLAGS)

# Anna-lise
main.o: main.c base.h
address.o: address.c address.h base.h
icmp_util.o: icmp_util.c icmp_util.h base.h checksum.h
ip_util.o: ip_util.c ip_util.h base.h address.h checksum.h
packet.o: packet.c packet.h base.h icmp_util.h ip_util.h address.h
checksum.o: checksum.c checksum.h

# Tests
unit_tests.o: unit_tests.c CUnit_util.h
test_base.o: test_base.c test_base.h CUnit_util.h base.h
test_icmp_util.o: test_icmp_util.c test_icmp_util.h CUnit_util.h icmp_util.h checksum.h
test_ip_util.o: test_ip_util.c test_ip_util.h ip_util.h checksum.h
test_address.o: test_address.c address.h manual_tests.h
test_checksum.o: test_checksum.c test_checksum.h checksum.h
test_packet.o: test_packet.c test_packet.h packet.h

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
