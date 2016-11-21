include ../Makefile.inc

GEN_EXE = ouch intquit t_kill sig_sender nonreentrant

# LINUX_EXE = 

EXE = ${GEN_EXE} 

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o

clean_mac :
	${RM} ${EXE} *.o
	${RM} -r ${EXE} *.dSYM

showall :
	@echo ${EXE}

${EXE} : ${TLPI_LIB}