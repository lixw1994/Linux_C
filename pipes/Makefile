include ../Makefile.inc

GENEXE = simple_pipe pipe_sync pipe_ls_wc popen_glob fifo_seqnum_server fifo_seqnum_client
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

pipe_sync : pipe_sync.c
	${CC} -o $@ pipe_sync.c ../time/curr_time.c ${CFLAGS} ${LDLIBS}
popen_glob : popen_glob.c
	${CC} -o $@ popen_glob.c ../procexec/print_wait_status.c ${CFLAGS} ${LDLIBS}
