include ../Makefile.inc

GENEXE = t_setsid t_setpriority
LINUXEXE = 

EXE = ${GENEXE} ${LINUXEXE}

all : ${EXE}

allgen : ${GENEXE}

clean :
	${RM} ${EXE} *.o

clean_mac:
	${RM} ${EXE} *.o
	${RM} -r ${EXE} *.dSYM

showall :
	@echo ${EXE}