include ../Makefile.inc

GENEXE = simple_thread thread_incr_mutex prod_condvar thread_multijoin

LINUXEXE =

EXE = ${GENEXE} ${LINUXEXE}

all : ${EXE}

allgen : {GENEXE}

clean :
	${RM} ${EXE} *.o

clean_mac:
	${RM} ${EXE} *.o
	${RM} -r ${EXE} *.dSYM

showall :
	@echo ${EXE}

${EXE} : ${TLPI_LIB}
