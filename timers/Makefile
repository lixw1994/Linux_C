include ../Makefile.inc

GEN_EXE = real_timer timed_read t_nanosleep

LINUX_EXE = demo_timerfd t_clock_nanosleep

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

# in Linux , 取消下面一行注释
# LDLIBS = ${IMPL_LDLIBS} ${LINUX_LIBRT}
	# Many of the programs in this directory need the 
	# realtime library, librt; to keep this Makefile simple,
	# we link *all* of the programs against that library.

clean : 
	${RM} ${EXE} *.o

clean_mac :
	${RM} ${EXE} *.o
	${RM} -r ${EXE} *.dSYM

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
