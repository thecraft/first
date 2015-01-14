SOURCE = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SOURCE))
LD = -lpthread

all:epoll
epoll: $(OBJS)
	cc $^ $(LD) -o $@ 

%.o:%.c
	cc  -c $^ -o $@ 

clean:
	rm -f *.o


