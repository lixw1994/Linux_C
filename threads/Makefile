include ../Makefile.inc

GENEXE = simple_thread thread_incr_mutex prod_condvar thread_multijoin2 \
		strerror_test thread_cancel thread_cleanup

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

strerror_test_tsd: strerror_test.o strerror_tsd.o
	${CC} -o $@ strerror_test.o strerror_tsd.o \
		${CFLAGS} ${LDLIBS}

strerror_test_tls: strerror_test.o strerror_tls.o
	${CC} -o $@ strerror_test.o strerror_tls.o \
	    	${CFLAGS} ${LDLIBS}
