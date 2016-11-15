#include "tlpi_hdr.h"

int main(int argc, char const *argv[])
{
	if(argc != 3 || strcmp(argv[1], "--help") == 0)
		usageErr("%s file\n", argv[0]);
	if(truncate(argv[1], getLong(argv[2], GN_ANY_BASE, "length")))
		errExit("truncate");
	exit(EXIT_SUCCESS);
	return 0;

}
