CC = gcc
LDC = gcc
LD=gfortran
FC=gfortran
LD_FLAGS = -fopenmp
FLAGS = -fopenmp
LDC_FLAGS= -lm -fopenmp
PROGC = LA4.cx
PROGF= LA4.x
RM= /bin/rm


#all rule

OBJSC=$(PROGC:%.cx=%C.o)
OBJSF=$(PROGF:%.x=%F.o)


all: $(PROGC)

$(PROGC): $(OBJSC)
	$(LDC)  $(OBJS) $< -o $@ $(LDC_FLAGS)

%C.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

$(PROGF): $(OBJSF)
	$(LD) $(LD_FLAGS) $(OBJS) $< -o $@

%F.o: %.f90
	$(FC) $(FLAGS) -c $^ -o $@



#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod

