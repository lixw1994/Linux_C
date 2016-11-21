include ../Makefile.inc

GEN_EXE = copy  t_truncate\
	seek_io t_readv

# LINUX_EXE = large_file

EXE = ${GEN_EXE} # ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean : 
	${RM} ${EXE} *.o

clean_mac :
	${RM} ${EXE} *.o
	${RM} -r ${EXE} *.dSYM

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
