include ../Makefile.inc

GEN_EXE = ouch intquit t_kill sig_sender

# LINUX_EXE = 

EXE = ${GEN_EXE} 

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o

showall :
	@echo ${EXE}

${EXE} : ${TLPI_LIB}