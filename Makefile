#
# Makefile for CSE 30 -- PA2
# You should not need to change anything in this file.
#

HEADERS		= pa2.h pa2Strings.h
C_SRCS		= main.c pa2Globals.c tickClock.c \
		  getCurrentTime.c interpretTime.c printClock.c
ASM_SRCS	= rangeCheck.s setClock.s incrementBCDValue.s printChar.s \
		  getRemainder.s convertTime.s

EC_C_SRCS	= mainEC.c pa2Globals.c tickClock.c \
		  getCurrentTime.c interpretTimeEC.c printClock.c chime.c

C_OBJS		= $(C_SRCS:.c=.o)
EC_C_OBJS	= $(EC_C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
OBJS		= $(C_OBJS) $(ASM_OBJS)
EC_OBJS		= $(EC_C_OBJS) $(ASM_OBJS)

EXE		= pa2
EC_EXE		= pa2EC
TEST_EXES	= testinterpretTime testsetClock testincrementBCDValue \
		  testtickClock

GCC		= gcc
ASM		= $(GCC)
RM		= rm

GCC_FLAGS	= -c -std=c99 -pedantic -Wall -D__EXTENSIONS__ -O3 -g \
		  -fomit-frame-pointer
ASM_FLAGS	= -c 
LD_FLAGS	= -Wall

#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EXE) $(OBJS) 
	@echo ""
	@echo "Compilation Successful!"

$(EC_EXE): $(EC_OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(EC_EXE) $(EC_OBJS) 
	@echo ""
	@echo "Compilation Successful!"

$(C_OBJS): $(HEADERS)

clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f $(EXE) $(EC_EXE) $(TEST_EXES) $(OBJS) $(EC_OBJS) *.ln core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make

#
# Unit test targets
#
testinterpretTime: test.h pa2.h interpretTime.o testinterpretTime.o \
	rangeCheck.o
	@echo "Compiling testinterpretTime.c"
	$(GCC) $(LD_FLAGS) -o testinterpretTime testinterpretTime.o \
	interpretTime.o rangeCheck.o
	@echo "Compilation Successful!"

testsetClock: test.h pa2.h setClock.o testsetClock.o pa2Globals.o \
	getRemainder.o 
	@echo "Compiling testsetClock.c"
	$(GCC) $(LD_FLAGS) -o testsetClock testsetClock.o \
	setClock.o pa2Globals.o getRemainder.o 
	@echo "Compilation Successful!"

testincrementBCDValue: test.h pa2.h incrementBCDValue.o \
	testincrementBCDValue.o
	@echo "Compiling testincrementBCDValue.c"
	$(GCC) $(LD_FLAGS) -o testincrementBCDValue testincrementBCDValue.o \
	incrementBCDValue.o
	@echo "Compilation Successful!"

testtickClock: test.h pa2.h testtickClock.o tickClock.o \
	incrementBCDValue.o pa2Globals.o
	@echo "Compiling testtickClock.c"
	$(GCC) $(LD_FLAGS) -o testtickClock testtickClock.o \
	tickClock.o incrementBCDValue.o pa2Globals.o
	@echo "Compilation Successful!"

testprintClock: test.h pa2.h testprintClock.o printClock.o \
	pa2Globals.o 
	@echo "Compiling testprintClock.c"
	$(GCC) $(LD_FLAGS) -o testprintClock testprintClock.o \
	printClock.o printChar.o
	@echo "Compilation Successful!"

testconvertTime: test.h pa2.h convertTime.o testconvertTime.o pa2Globals.o 
	@echo "Compiling testconvertTime.c"
	$(GCC) $(LD_FLAGS) -o testconvertTime testconvertTime.o \
	convertTime.o pa2Globals.o 
	@echo "Compilation Successful!"


	

