CC= g++
ASM= nasm
LD= g++
CFLAGS=-c -g -O0 -Wall
AFLAGS= -f elf64
LDFLAGS= -g -no-pie
VPATH = ./src
CMPPATH = ./compile
SRCC = unit_test.cpp
HEAD = mvector.hpp mvectorbool.hpp mexcpt.hpp mvectorimplem.cpp mvectorboolimplem.cpp
SRCSASM = 
OBJC = $(SRCC:.cpp=.o)
OBJASM = $(SRCASM:.S=.o)
EXECUTABLE = run

all: $(CMPPATH) $(SRCC) $(SRCASM) $(EXECUTABLE)

$(CMPPATH):
	mkdir $@

$(EXECUTABLE): $(CMPPATH)/$(OBJC)
	$(LD) $(LDFLAGS) $(CMPPATH)/$(OBJC) -o $@

$(CMPPATH)/%.o: %.cpp $(HEAD)
	$(CC) $(CFLAGS) $< -o $@

$(CMPPATH)/%.o: %.S
	$(ASM) $(AFLAGS) $< -o $@