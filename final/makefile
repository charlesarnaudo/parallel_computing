CC = mpicc
LDC = mpicc
LD_FLAGS =  -fopenmp
FLAGS = -Wall -fopenmp
RM= /bin/rm

CPROGS = final.cx

OBJSC=$(CPROGS:%.cx=%C.o)

#all rule
all: $(CPROGS)


$(CPROGS):$(OBJSC)
	$(LDC) $(LD_FLAGS) $^ -o $@

%C.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@



#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod

