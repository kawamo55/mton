
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "mton.h"

static char ibuf[MAXBUFF];

static void siftOut(int n)
{
	int i;
	for(i=n; i>0; i--){
		outb[i]=outb[i-1];
	}
	outb[0]=' ';
}

int mton()
{
	int i=0,r=0,dig;
#if DEBUG==1
	printf("__mton start\n");
#endif

	// mval to int
	while(ibuf[i]) {
		dig=isVal(ibuf[i++]);
		if (dig>-1) {
			r *= mval;
			r += dig;
		} else {
			r=-1;
			break;
		}
	}
#if DEBUG==1
	printf("__mton=%d\n",r);
#endif

	// int to nval
	if (r>-1) {
		outb[(i=0)]='\0';
	    while(r) {
			siftOut(++i);
			outb[0]=ctbl[(r % nval)];
#if DEBUG==1
	printf("__mton=%d\n",(r % nval));
#endif
			r = (int)(r / nval);
		}
	}
	return r;
}

int setargv(int argc, char *argv[]) 
{
	int ret=0,i,j=0;

#if DEBUG==1
	printf("__setarg=%d\n",argc);
#endif
	for(i=1; i<argc; i++) {
		if (!strcmp(argv[i],"-n") && i<argc) {
			if (argv[i+1][0]=='-') {
				ret=-1;
				fprintf(stderr,"-n value error\n");
				break;
			} else
				nval=atoi(argv[++i]);
#if DEBUG==1
	printf("__nval=%s\n",nval);
#endif
		} else if (!strcmp(argv[i],"-m") && i<argc) {
			if (argv[i+1][0]=='-') {
				fprintf(stderr,"-m value error\n");
				ret=-1;
				break;
			} else
				mval=atoi(argv[++i]);
#if DEBUG==1
	printf("__mval=%s\n",mval);
#endif
		} else if (argv[i][0]=='-') {
			fprintf(stderr,"Option error \n");
			ret=-1;
			break;
		} else {
			while(argv[i][j]) {
				if (j<(MAXBUFF-1)) {
					ibuf[j]=toupper(argv[i][j]);
					if (isVal(ibuf[j])==-1) {
						fprintf(stderr,"value error\n");
						ret=-1;
						break;
					}
					j++;
					ibuf[j]='\0';
				} else {
					fprintf(stderr,"buffer overflow error\n");
					ret=-1;
					break;
				}
				ret=j;
			}
#if DEBUG==1
	printf("__ibuf=%s\n",ibuf);
#endif
		}
	}
	return ret;
}

int isVal(int c)
{
	int i=0,r=-1;

	while(ctbl[i]) {
		if (ctbl[i]==c) { r=i; break; }
		i++;
	}

	return r;
}
