
EXECS	=	main

all:	$(EXECS)

main.o:	main.c

OBJS	=	 main.o

clean:
	/bin/rm -f $(EXECS) $(OBJS) core a.out .nfs*

main:		$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main $(LDFLAGS)
