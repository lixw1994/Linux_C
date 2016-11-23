#ifndef SIGNAL_FUNCTIONS_H
#define SIGNAL_FUNCTIONS_H

// 显示信号集的函数
#include "../lib/tlpi_hdr.h"
#include <string.h>

void printSigset(FILE* of, const char* prefix, const sigset_t* sigset);

int printSigMask(FILE* of, const char* msg);

int printPendingSigs(FILE* of, const char* msg);

#endif
