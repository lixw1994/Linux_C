include ../Makefile.inc

GEN_EXE = t_fork fork_file_sharing t_vfork fork_whos_on_first fork_sig_sync \
		fork_stdio_buf multi_wait child_status

LINUX_EXE = exit_handlers

EXE = ${GEN_EXE} ${LINUX_EXE}

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

fork_sig_sync : fork_sig_sync.c
	${CC} -o $@ fork_sig_sync.c ../time/curr_time.c ${CFLAGS} ${LDLIBS}
multi_wait : multi_wait.c
	${CC} -o $@ multi_wait.c ../time/curr_time.c ${CFLAGS} ${LDLIBS}
child_status : child_status.c
	${CC} -o $@ child_status.c print_wait_status.c ${CFLAGS} ${LDLIBS}
	