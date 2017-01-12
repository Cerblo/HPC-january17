TARGET_SER	= poisson_ser
TARGET_PAR	= poisson_par
CC = suncc
DEPS = datatools.h jacobian.h init.h gauss_seidel.h jacobian_par.h
OPT = -g -fast
ISA =
PARA = -xopenmp
F90C  	= f90
CFLAGS = $(OPT) 
OBJECTS = datatools.o jacobian.o init.o main.o gauss_seidel.o jacobian_par.o
LIBS = 

$(TARGET_SER): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

$(TARGET_PAR): $(OBJECTS)
	$(CC) $(CFLAGS) $(PARA) -o $@ $(OBJECTS) $(LIBS)

clean: 
	@/bin/rm -f *.o core
realclean: clean
	@rm -f $(TARGET_SER) $(TARGET_PAR)

#rules
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

#file dependencies
datatools.o: datatools.c datatools.h
main.o: main.c datatools.h jacobian.h init.h gauss_seidel.h
init.o: init.c init.h
jacobian.o : jacobian.c jacobian.h
gauss_seidel.o : gauss_seidel.c gauss_seidel.h
jacobian_par.o : jacobian_par.c jacobian_par.h

