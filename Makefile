SRCS	= main.c datatools.c matmult_nat.c matmult_lib.c matmult_blk.c
OBJS	= $(SRCS:.c=.o)
TARGET	= madd.$(CC)

CC	= gcc
INCS	=
DBG	= -g
OPT	= -O3
PARA	= 
Cflags	= $(Dbg) $(OPT) $(PARA) $(XOPTS)

LIBS	= -L /usr/lib64/atlas -lcblas

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	@/bin/rm -f $(OBJS) *~ core*

realclean: clean
	@/bin/rm -f $(TARGET)
