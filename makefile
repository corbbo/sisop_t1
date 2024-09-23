_APP = t1_sisop
_MAIN_NAME = t1
_DASH_O = t1.o cpu_scheduler.o Processlist.o Process.o 
_CFLAGS = -c #-DDEBUG

all: $(_APP)

$(_APP): $(_DASH_O)
	g++ -o $(_APP) $(_DASH_O)

t1.o:	t1.cpp cpu_scheduler.h 
	g++ ${_CFLAGS} t1.cpp

cpu_scheduler.o: Processlist.cpp Processlist.h
	g++ ${_CFLAGS} cpu_scheduler.cpp

Processlist.o: Processlist.cpp Process.h
	g++ ${_CFLAGS} Processlist.cpp
	
Process.o: Process.cpp
	g++ ${_CFLAGS} Process.cpp

clean: 			
	rm -f ${_DASHOES} ${_APP}