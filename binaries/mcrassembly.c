#include<stdio.h>
int main()
{
int no = 100, val ;
printf("---The Program starts---");

        asm("mov %1, r0;"
           "mcr 2,5,r3,c5,c6;"
             "mov r0, %0;"
             : "=r" ( val )        /* output */
             : "r" ( no )         /* input */
             : "r0" /* clobbered register */
         );
printf("---------Program ends---");
printf("\nVAL: %d",val);
return 0;	
}


