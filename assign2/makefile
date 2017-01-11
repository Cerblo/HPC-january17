TARGET	= poisson
CC = gcc
DEPS = datatools.h jacobian.h func.h
OPT = -g -O3
ISA =
PARA =
F90C  	= f90
WARN = -Wall
CFLAGS = $(OPT) $(WARN) 
OBJECTS = datatools.o jacobian.o func.o main.o
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
main.o: main.c datatools.h jacobian.h func.h
func.o: func.c func.h
jacobian.o : jacobian.c jacobian.h


