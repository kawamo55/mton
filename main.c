
#include <stdio.h>
#include "mton.h"

const char usage[]="mton [Option] number_string\n\nOption:\n-m number [2 - 36] default 10\n-n number [2 - 36] default 16\n";

int  mval,nval;
char ctbl[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char outb[MAXBUFF];

int main(int argc, char *argv[])
{
	int r;

#if DEBUG==1
	printf("argc=%d\n",argc);
#endif
	if (argc==2 || argc==4 || argc==6) {
		mval=10;
		nval=16;
		r = setargv(argc, argv);
		if (r >= 0) r = mton();
		if (r >= 0) printf("to %s\n",outb);
	} else {
		printf(usage);
	}
}

