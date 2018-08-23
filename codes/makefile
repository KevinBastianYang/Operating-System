.PHONY: all
all : MyCopy ForkCopy Sig PipeCopy MyShell MoreShell DupShell

MyCopy : MyCopy.o
	gcc -o MyCopy MyCopy.o
MyCopy.o:MyCopy.c
	gcc -c MyCopy.c

ForkCopy:ForkCopy.o
	gcc -o ForkCopy ForkCopy.o
ForkCopy.o:ForkCopy.c
	gcc -c ForkCopy.c

Sig:sig.o
	gcc -o Sig sig.o
sig.o:sig.c
	gcc -c sig.c

PipeCopy:PipeCopy.o
	gcc -o PipeCopy PipeCopy.o
PipeCopy.o:PipeCopy.c
	gcc -c PipeCopy.c

#SockCopy:SockCopy.o
#	gcc -o SockCopy SockCopy.o
#SockCopy.o:SockCopy.c
#	gcc -c SockCopy.c

MyShell:MyShell.o
	gcc -o MyShell MyShell.o
MyShell.o:MyShell.c
	gcc -c MyShell.c

MoreShell:MoreShell.o
	gcc -o MoreShell MoreShell.o
MoreShell.o:MoreShell.c
	gcc -c MoreShell.c

DupShell:DupShell.o
	gcc -o DupShell DupShell.o
DupShell.o:DupShell.c
	gcc -c DupShell.c

clean:
	rm MyCopy ForkCopy Sig PipeCopy  MyShell MoreShell DupShell MyCopy.o ForkCopy.o sig.o PipeCopy.o MyShell.o MoreShell.o DupShell.o
