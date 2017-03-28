#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>

#define MAX_ERROR_LEN 256

static char buf[MAX_ERROR_LEN];

char* strerror_my(int err)
{
	if(err < 0 || err >= sys_nerr || sys_errlist[err] == NULL)
		snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err);
	else
	{
		strncpy(buf, sys_errlist[err], MAX_ERROR_LEN);
		buf[MAX_ERROR_LEN-1] = '\0';
	}

	return buf;
}
