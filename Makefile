CC = gcc
CFLAGS = -Werror -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -std=c99 -D_GNU_SOURCE

.PHONEY: all
all: main 

.PHONEY: clean
clean:
	$(RM) test dynamicarray/darray.o linkedlist/slist.o linkedlist/dlist.o hashtable/hashtable.o

main: main.c dynamicarray/darray.o linkedlist/slist.o linkedlist/dlist.o hashtable/hashtable.o
