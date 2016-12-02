include ../Makefile.inc

GENEXE = simple_pipe pipe_sync pipe_ls_wc
LINUXEXE = 

EXE = ${GENEXE} ${LINUXEXE}

all : ${EXE}

allgen : ${GENEXE}

clean :
	${RM} ${EXE} *.o

clean_mac :
	${RM} ${EXE} *.o
	${RM} -r ${EXE} *.dYSM

showall : 
	@echo ${EXE}

${EXE} : ${TLPI_LIB}

pipe_sync : pipe_sync.c
	${CC} -o $@ pipe_sync.c ../time/curr_time.c ${CFLAGS} ${LDLIBS}
