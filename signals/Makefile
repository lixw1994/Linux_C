include ../Makefile.inc

GEN_EXE = ouch intquit t_kill sig_sender nonreentrant t_sigaltstack \

# sig_receiver 

# LINUX_EXE = t_sigqueue

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

sig_receiver : sig_receiver.c
	${CC} -D_BSD_SOURCE -o $@ sig_receiver.c signal_functions.c ${CFLAGS} ${LDLIBS}

nonreentrant : nonreentrant.o
	${CC} -o $@ nonreentrant.o ${CFLAGS} ${LDLIBS} # ${LINUX_LIBCRYPT}