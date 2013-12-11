CC = gcc

SPATH = src
OPATH = obj
BPATH = bin
HPATH = include
DPATH = doc

CFLAGS = -std=gnu99 -pedantic -Werror -W -Wall -Wextra -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wshadow -Wbad-function-cast -Wcast-qual
IFLAGS = -I$(HPATH)

vpath %.c $(SPATH)/
vpath %.h $(HPATH)/
vpath %.o $(OPATH)/

all: anna-lise

anna-lise: main.o | bin
		$(CC) $(CFLAGS) -o $(BPATH)/$@ $(OPATH)/main.o

%.o: %.c | obj
		$(CC) $(CFLAGS) -o $(OPATH)/$@ -c $< $(IFLAGS)

main.o: main.c base.h

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
