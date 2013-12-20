CC = gcc

SPATH = src
OPATH = obj
BPATH = bin
HPATH = include
DPATH = doc
TPATH = tests
LPATH = lib

CFLAGS = -std=gnu99 -pedantic -Werror -W -Wall -Wextra -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual -g
IFLAGS = -I$(HPATH) -I$(TPATH)
LFLAGS = -L/usr/lib -L/usr/lib64 -L$(LPATH)

vpath %.c $(SPATH)/ $(TPATH)/
vpath %.h $(HPATH)/ $(TPATH)/
vpath %.o $(OPATH)/
vpath %.a $(LPATH)/

all: anna-lise

anna-lise: main.o libanna.a ping_icmp.o | bin
		$(CC) $(CFLAGS) $(LFLAGS) -o $(BPATH)/$@ $(OPATH)/main.o $(OPATH)/ping_icmp.o -lanna

tests: unit_tests other_tests

unit_tests: unit_tests.o libanna.a libunittests.a | bin
	$(CC) $(CFLAGS) $(LFLAGS) -o $(BPATH)/unit_tests $(OPATH)/unit_tests.o -lcunit -lunittests -lanna

other_tests: test_address test_traceroute | bin

test_address: test_address.o address.o | bin
	$(CC) $(CFLAGS) -o $(BPATH)/test_address $(OPATH)/test_address.o $(OPATH)/address.o

test_traceroute: test_traceroute.o libanna.a | bin
	$(CC) $(CFLAGS) $(LFLAGS) -o $(BPATH)/test_traceroute $(OPATH)/test_traceroute.o -lanna

%.o: %.c | obj
		$(CC) $(CFLAGS) -o $(OPATH)/$@ -c $< $(IFLAGS)

# Anna-lise
main.o: main.c base.h address.h icmp_util.h ip_util.h packet.h ping_icmp.h
ping_icmp.o: ping_icmp.c ping_icmp.h base.h address.h icmp_util.h ip_util.h packet.h time_util.h
address.o: address.c address.h base.h
icmp_util.o: icmp_util.c icmp_util.h base.h checksum.h
ip_util.o: ip_util.c ip_util.h base.h address.h checksum.h
packet.o: packet.c packet.h base.h icmp_util.h ip_util.h address.h
checksum.o: checksum.c checksum.h
traceroute.o: traceroute.c traceroute.h base.h address.h packet.h time_util.h
time_util.o: time_util.c time_util.h base.h
udp_util.o: udp_util.c udp_util.h base.h ip_util.h address.h

libanna.a: address.o icmp_util.o ip_util.o packet.o checksum.o traceroute.o time_util.o udp_util.o | lib
		ar -crv $(LPATH)/libanna.a $(OPATH)/address.o $(OPATH)/icmp_util.o $(OPATH)/ip_util.o $(OPATH)/packet.o $(OPATH)/checksum.o $(OPATH)/traceroute.o $(OPATH)/time_util.o $(OPATH)/udp_util.o
		ranlib $(LPATH)/libanna.a

# Tests
unit_tests.o: unit_tests.c CUnit_util.h
test_base.o: test_base.c test_base.h CUnit_util.h base.h
test_icmp_util.o: test_icmp_util.c test_icmp_util.h CUnit_util.h icmp_util.h checksum.h
test_ip_util.o: test_ip_util.c test_ip_util.h ip_util.h checksum.h
test_address.o: test_address.c address.h manual_tests.h
test_checksum.o: test_checksum.c test_checksum.h checksum.h
test_packet.o: test_packet.c test_packet.h packet.h
test_traceroute.o: test_traceroute.c traceroute.h address.h packet.h

libunittests.a: test_base.o test_icmp_util.o test_ip_util.o test_address.o test_checksum.o test_packet.o | lib
		ar -crv $(LPATH)/libunittests.a $(OPATH)/test_base.o $(OPATH)/test_icmp_util.o $(OPATH)/test_ip_util.o $(OPATH)/test_address.o $(OPATH)/test_checksum.o $(OPATH)/test_packet.o
		ranlib $(LPATH)/libunittests.a

doc: cleandoc
		@doxygen
obj:
		@mkdir -p $(OPATH)

bin:
		@mkdir -p $(BPATH)

lib:
		@mkdir -p $(LPATH)

clean:
		@rm -rf $(OPATH) $(BPATH) $(LPATH)

cleandoc:
		@rm -rf $(DPATH)

cleanall: clean cleandoc
		@echo "Clean."

archive:
		@tar -cvzf $(shell basename `pwd).tar.gz $(SPATH) $(HPATH) makefile Doxyfile AUTHORS COPYING LICENSE README README.md
