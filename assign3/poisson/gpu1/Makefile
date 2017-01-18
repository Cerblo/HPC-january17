TARGET	= poisson
OBJS	= main.o jacobian.o init.o datatools.o 

OPT	= -g
ISA	= 
PARA	=

XOPTS = -G -Xptxas=-v		#from cuda makefile
ARCH  = -arch=sm_30		#from cuda makefile
OMP   = -fopenmp 		#from cuda makefile

CCC	= nvcc
CXX	= nvcc			
CXXFLAGS= 

CFLAGS	= $(OPT) $(ISA) $(PARA) $(XOPT)

F90C  	= f90

LIBS	=  

CUDA_PATH ?= /appl/cuda/8.0
INCLUDES = -I$(CUDA_PATH)/include -I$(CUDA_PATH)/samples/common/inc

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CCC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

.SUFFIXES: .cu
.cu.o:
	$(CXX) -o $*.o -c $*.cu $(CXXFLAGS) $(SOFLAGS) $(INCLUDES)


clean:
	@/bin/rm -f *.o core

realclean: clean
	@rm -f $(TARGET)

# dependencies
#
main.o  : main.cu datatools.h
jacobian.o: jacobian.cu
init.o: init.cu init.h datatools.h
