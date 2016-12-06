include ../Makefile.inc

GENEXE = us_xfr_sv us_xfr_cl ud_ucase_sv ud_ucase_cl \
		i6d_ucase_sv i6d_ucase_cl

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
