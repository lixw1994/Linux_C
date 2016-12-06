include ../Makefile.inc

GENEXE = svmsg_create

LINUXEXE = 

EXE = ${GENEXE} ${LINUXEXE}

all : ${EXE}

allgen : ${GENEXE}

clean :
	${RM} ${EXE} *.o

clean_mac :
	${RM} ${EXE} *.o
	${RM} -r ${EXE} *.dSYM

showall :
	@echo ${EXE}

${EXE} : ${TLPI_LIB}
