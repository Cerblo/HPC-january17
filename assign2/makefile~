TARGET	= poisson
CC = gcc
DEPS = datatools.h jacobian.h init.h gauss_seidel.h
OPT = -g -O3
ISA =
PARA =
F90C  	= f90
WARN = -Wall
CFLAGS = $(OPT) $(WARN) 
OBJECTS = datatools.o jacobian.o init.o main.o gauss_seidel.o
LIBS = 

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

clean: 
	@/bin/rm -f *.o core
realclean: clean
	@rm -f poisson

#rules
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

#file dependencies
datatools.o: datatools.c datatools.h
main.o: main.c datatools.h jacobian.h init.h gauss_seidel.h
init.o: init.c init.h
jacobian.o : jacobian.c jacobian.h
gauss_seidel.o : gauss_seidel.c gauss_seidel.h

