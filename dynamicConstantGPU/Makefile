.SUFFIXES:  .cpp .cu .o
CUDA_HOME := /usr/local/cuda
INC     := -I$(CUDA_HOME)/include -I.
LIB     := -L$(CUDA_HOME)/lib -lcudart
CC      := nvcc
OBJS    := quicksort.o kSqBoxAlgorithm.o
DEP     :=

NVCCFLAGS       := -lineinfo -arch=sm_53 -g
DYNCUDAFLAGS    := -arch=compute_35 -rdc=true -lcudadevrt

all:    kSqBoxAlgorithm

kSqBoxAlgorithm: quicksort.o kSqBoxAlgorithm.o $(DEP)
	$(CC) $(INC) $(DYNCUDAFLAGS) -o kSqBoxAlgorithm $(OBJS) $(LIB)

.cpp.o:
	$(CC) $(INC) $(NVCCFLAGS) -c $< -o $@

.cu.o:
	$(CC) $(INC) $(DYNCUDAFLAGS) -c $< -o $@

clean:
	rm -f *.o kSqBoxAlgorithm

