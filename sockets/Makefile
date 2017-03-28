include ../Makefile.inc.MacOSX

GENEXE = us_xfr_sv us_xfr_cl ud_ucase_sv ud_ucase_cl \
		i6d_ucase_sv i6d_ucase_cl is_seqnum_sv is_seqnum_cl

LINUXEXE = 

EXE = ${GENEXE} ${LINUXEXE}

all : ${EXE}

allgen : ${GENEXE}

is_seqnum_sv : is_seqnum_sv.c
	${CC} -o $@ is_seqnum_sv.c read_line.c ${CFLAGS} ${LDLIBS}
is_seqnum_cl : is_seqnum_cl.c
	${CC} -o $@ is_seqnum_cl.c read_line.c ${CFLAGS} ${LDLIBS}

clean :
	${RM} ${EXE} *.o

clean_mac :
	${RM} ${EXE} *.o
	${RM} -r ${EXE} *.dSYM

showall :
	@echo ${EXE}

${EXE} : ${TLPI_LIB}
