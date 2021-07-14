
EXECS	=	main
CFLAGS = -g

all:	$(EXECS)

main.o:	main.c util.h world.h world_physics.h

util.o:	util.c util.h

world.o:	world.c world.h

world_physics.o:	world_physics.c world_physics.h

OBJS	=	 main.o util.o world.o world_physics.o

clean:
	/bin/rm -f $(EXECS) $(OBJS) core a.out .nfs*

main:		$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main $(LDFLAGS)
