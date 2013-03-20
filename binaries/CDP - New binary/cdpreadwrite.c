#include<stdio.h>
int main()
{
int no = 100, val ;
printf("---The Program starts---");

  asm("mov %1, r0;"

	     "cdp p0,0x0,c1,c2,c3;"
	     "cdp p0,0x0,c1,c2,c2;"
	     "cdp p0,0x0,c5,c4,c3;"
	     "cdp p0,0x0,c5,c4,c2;"
	     "cdp p0,0x0,c5,c4,c3;"
	     "cdp p0,0x0,c5,c4,c2;"
	     "cdp p0,0x0,c7,c6,c3;"
	     "cdp p0,0x0,c7,c6,c2;"
//	     "cdp p0,0x0,c10,c10,c3;"
//	     "cdp p0,0x0,c1,c2,c3;"
//	     "cdp p0,0x0,c1,c2,c3;"
//	     "cdp p0,0x0,c1,c2,c3;"
//	     "cdp p0,0x0,c1,c2,c3;"

             "mov r1, %0;"
             : "=r" ( val )        /* output */
             : "r" ( no )         /* input */
             : "r0" /* clobbered register */
         );

printf("---------Program ends---");
printf("\nVAL: %d",val);
return 0;
}


