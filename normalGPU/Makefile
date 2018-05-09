.SUFFIXES:  .cpp .cu .o
CUDA_HOME := /usr/local/cuda
INC	:= -I$(CUDA_HOME)/include -I.
LIB	:= -L$(CUDA_HOME)/lib 
CC	:= nvcc
OBJS	:= kSqBoxAlgorithm.o
DEP	:=  

NVCCFLAGS	:= -lineinfo -arch=sm_53 -g

all:	kSqBoxAlgorithm

kSqBoxAlgorithm:	$(OBJS) $(DEP)
	$(CC) $(INC) $(NVCCFLAGS) -o kSqBoxAlgorithm $(OBJS) $(LIB)

.cpp.o:
	$(CC) $(INC) $(NVCCFLAGS) -c $< -o $@ 

.cu.o:
	$(CC) $(INC) $(NVCCFLAGS) -c $< -o $@
	

clean:
	rm -f *.o kSqBoxAlgorithm


