include ../Makefile.inc

GENEXE = simple_thread

LINUXEXE =

EXE = ${GENEXE} ${LINUXEXE}

all : ${EXE}

allgen : {GENEXE}

clean :
	${RM} ${EXE} *.o

clean_mac:
	${RM} -r ${EXE} *.dYSM

showall :
	@echo ${EXE}

${EXE} : ${TLPI_LIB}
