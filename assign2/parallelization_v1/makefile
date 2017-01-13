TARGET	= poisson
CC = suncc
DEPS = datatools.h jacobian.h init.h
OPT = -g -fast
ISA =
PARA = -xopenmp -xinstrument=datarace
F90C  	= f90
CFLAGS = $(OPT) $(PARA)
OBJECTS = datatools.o jacobian.o init.o main.o
LIBS = 

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

clean: 
	@/bin/rm -f *.o core
realclean: clean
	@rm -f $(TARGET)

#rules
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

#file dependencies
datatools.o: datatools.c datatools.h
main.o: main.c datatools.h jacobian.h init.h
init.o: init.c init.h
jacobian.o : jacobian.c jacobian.h

